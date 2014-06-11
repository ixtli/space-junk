//
//  server.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/1/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include <functional>
#include <thread>

#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "webSocketSession.h"
#include "crypto.h"

#include "server.h"

#pragma mark -
#pragma mark Application agnostic helper methods for POSIX networking

// get sockaddr, IPv4 or IPv6:
void* Server::get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int Server::acceptConnection(int acceptingSocket)
{
	struct sockaddr_storage addrStorage;
	socklen_t len = sizeof(addrStorage);
	struct sockaddr* address = (struct sockaddr*) &addrStorage;
	
	int ret = accept(acceptingSocket, address, &len);
	
	if (ret < 0)
	{
		error("accept() failed.");
	} else {
		char remoteIP[INET6_ADDRSTRLEN + 1];
		inet_ntop(addrStorage.ss_family,
							get_in_addr(address),
							remoteIP,
							INET6_ADDRSTRLEN);
		info("New connection from %s on socket %d", remoteIP, ret);
	}
	
	return ret;
}

int Server::openConnection(const char *host, unsigned int port)
{
	int fd = -1;
	
	// The easiest way to interrupt a call to select() is to give it some
	// data. So we make a single request and ignore the outcome
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	char portName[6];
	sprintf(portName, "%u", port);
	struct addrinfo *serverInfo;
	int errorCode = getaddrinfo("localhost", portName, &hints, &serverInfo);
	if (errorCode)
	{
		error("Couldn't write closing packet: %s", gai_strerror(errorCode));
		return fd;
	}
	
	// Loop through all of the sockets until we find one we can use
	struct addrinfo* p;
	for(p = serverInfo; p != NULL; p = p->ai_next)
	{
		fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (fd == -1)
		{
			error("socket()");
			continue;
		}
		
		if (connect(fd, p->ai_addr, p->ai_addrlen) < 0)
		{
			int errsv = errno;
			close(fd);
			fd = -1;
			error("connect(): %i", errsv);
			continue;
		}
		
		break;
	}
	
	// We never found anything
	if (p == NULL)
	{
		return fd;
	}
	
	// Get address data from newly found connection
	char s[INET6_ADDRSTRLEN];
	inet_ntop(p->ai_family, get_in_addr(p->ai_addr), s, sizeof(s));
	
	// Clean up!
	freeaddrinfo(serverInfo);
	
	return fd;
}

int Server::listenForConnections(unsigned int port)
{
	char portName[6]; // 0xFF base 10 diget count + 1 for \0
	sprintf(portName, "%u", port);
	
	// Get us a socket and bind it. Start by clearing hints struct
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	// Get info for this portname
	struct addrinfo* ai;
	int rv = getaddrinfo(NULL, portName, &hints, &ai);
	
	// Check errors to make sure we're ok so far
	if (rv)
	{
		error("getaddrinfo error: %s", gai_strerror(rv));
		return -1;
	}
	
	// Bind to socket
	int listeningSocket = -1;
	struct addrinfo* p;
	for (p = ai; p != NULL; p = p->ai_next)
	{
		listeningSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listeningSocket < 0)
		{
			continue;
		}
		
		// skip the "address already in use" warnings
		// Needs to be passed as a param below
		const int yes = 1;
		setsockopt(listeningSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		
		// Call bind() to associate this process with the socket
		if (bind(listeningSocket, p->ai_addr, p->ai_addrlen) < 0)
		{
			close(listeningSocket);
			continue;
		}
		
		// Found a good one
		break;
	}
	
	// If p still unbound, means we were never able to bind
	if (p == NULL)
	{
		error("Failed to bind to port %s", portName);
		return -1;
	}
	
	// No longer need ai struct pointer
	freeaddrinfo(ai);
	
	// Listen on port newly bound to our process
	int connectionBacklogSize = 10;
	if (listen(listeningSocket, connectionBacklogSize) == -1)
	{
		error("Listen failed.");
		return -1;
	}
	
	info("Listening on port: %s", portName);
	
	return listeningSocket;
}

#pragma mark -
#pragma mark Simple POSIX select() server

Server Server::_instance;

bool Server::_shouldTerminateThread = false;

std::thread* serverThread = NULL;

Server::Server() :

_listeningPort(0)

{ }

Server::~Server()
{
	stop();
}

void Server::awaitConnection(int listeningSocket)
{
	// Initialize sets
	fd_set master_fds;
	fd_set read_fds;
	FD_ZERO(&master_fds);
	FD_ZERO(&read_fds);
	
	// Add the listener to the master set
	FD_SET(listeningSocket, &master_fds);
	
	// Keep track of the biggest file descriptor
	int largestFileDescriptor = listeningSocket;
	
	// We keep a hash of open websocket sessions. These pointers facilitate that
	OpenSession* currentSession = NULL;
	OpenSession* _sessionHead = NULL;
	
	// When the application begins to shut down, this bit will get flipped
	// and the thread will terminate
	while (!_shouldTerminateThread)
	{
		// Copy master file descriptor
		read_fds = master_fds;
		
		// The infamous select() function
		if (select(largestFileDescriptor + 1, &read_fds, NULL, NULL, NULL) == -1)
		{
			error("Select failed.");
			return;
		}
		
		// Run through existing connections looking for data to read
		for (int i = 0; i <= largestFileDescriptor; i++)
		{
			if (!FD_ISSET(i, &read_fds))
			{
				continue;
			}
			
			// We got a connection!
			if (i == listeningSocket)
			{
				int newFileDescriptor = acceptConnection(listeningSocket);
				
				// Error checking
				if (newFileDescriptor == -1)
				{
					continue;
				}
				
				// Keep track of largest file descriptor
				FD_SET(newFileDescriptor, &master_fds);
				if (newFileDescriptor > largestFileDescriptor)
				{
					largestFileDescriptor = newFileDescriptor;
				}
				
				// Configure the open session structure and save the new file descriptor
				OpenSession* n = new OpenSession();
				n->session = NULL;
				n->fileDescriptor = newFileDescriptor;
				
				// Add to the hash of open sessions
				HASH_ADD_INT(_sessionHead, fileDescriptor, n);
				
				continue;
			}
			
			// Find the one that sent us a message
			currentSession = NULL;
			HASH_FIND_INT(_sessionHead, &i, currentSession);
			
			if (!currentSession)
			{
				error("Couldn't find session.");
				continue;
			}
			
			// If we've never gotten a message from this endpoint before, init session
			if (!currentSession->session)
			{
				currentSession->session = new WebSocketSession(i);
				currentSession->session->init();
			} else {
				// Otherwise read new data
				currentSession->session->newData();
			}
			
			// Any number of interactions could have caused the session to close
			// so trap for all of them, even directly after init
			if (!currentSession->session->open())
			{
				// Clean up session
				HASH_DEL(_sessionHead, currentSession);
				delete currentSession->session;
				delete currentSession;
				
				// Clean up socket
				if (FD_ISSET(i, &master_fds))
				{
					close(i);
					FD_CLR(i, &master_fds);
				}
			}
		}
	}
	
	info("Caught exit signal. Cleaning up.");
	
	// Clean up
	for (int i = 0; i <= largestFileDescriptor; i++)
	{
		// Check to see if we've registered a session for this file descriptor
		currentSession = NULL;
		HASH_FIND_INT(_sessionHead, &i, currentSession);
		
		if (currentSession)
		{
			// If so, deallocate all memory associated with it
			HASH_DEL(_sessionHead, currentSession);
			delete currentSession->session;
			delete currentSession;
		}

		if (FD_ISSET(i, &master_fds))
		{
			close(i);
			FD_CLR(i, &master_fds);
		}
	}
	
	// Make sure everything is deallocated
	HASH_CLEAR(hh, _sessionHead);
}

bool Server::init()
{
	info("Socket server initialization.");
	
	// Ignore SIG_PIPE on this thread.
	signal(SIGPIPE, SIG_IGN);
	
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	
	sa.sa_handler = SIG_IGN;
	
	if (-1 == sigaction(SIGPIPE, &sa, NULL))
	{
		perror("sigaction() failed");
	}
	
	return true;
}

bool Server::run(unsigned int port)
{
	if (isRunning())
		return false;
	
	int listeningSocket = listenForConnections(port);
	
	if (listeningSocket < 0)
	{
		return false;
	}
	
	_listeningPort = port;
	_shouldTerminateThread = false;
	
	// Thread dispatch in 21st century C++
	auto fxn = std::bind(Server::awaitConnection, listeningSocket);
	serverThread = new std::thread(fxn);
	
	return true;
}

bool Server::stop()
{
	if (!isRunning())
		return false;
	
	// Tell the thread to stop once select() returns
	_shouldTerminateThread = true;
	
	// select() sleeps until new data, so we have to handshake with it to wake it
	int fd = openConnection("localhost", _listeningPort);
	if (fd < 0)
	{
		error("Failed to connect to self in order to close server.");
		return false;
	}
	
	// The handshake is enough to wake select()
	close(fd);
	
	// It's possible that the thread ended faster than close() took, so check
	// to see if it's joinable.
	if (serverThread->joinable())
	{
		info("Waiting for server to clean up...");
		serverThread->join();
		info("Server thread joined.");
	}
	
	// Clean up so run can be called again
	delete serverThread;
	serverThread = NULL;
	
	return true;
}

bool Server::isRunning() const
{
	return (serverThread != NULL);
}

