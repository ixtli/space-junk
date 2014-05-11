//
//  server.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/1/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include <thread>

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
#pragma mark Helper methods for

// get sockaddr, IPv4 or IPv6:
void* Server::get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

#pragma mark -
#pragma mark Implementation of basic POSIX socket server

Server Server::_instance;

bool Server::_shouldTerminateThread;

Server::Server()
{ }

Server::~Server()
{
	_shouldTerminateThread = true;
}

void Server::awaitConnection()
{
	// @TODO: load this
	const char* kPortName = "9038";
	
	// Initialize sets
	fd_set master_fds;
	fd_set read_fds;
	
	FD_ZERO(&master_fds);
	FD_ZERO(&read_fds);
	
	// Get us a socket and bind it. Start by clearing hints struct
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	// Get info for this portname
	struct addrinfo* ai;
	int rv = getaddrinfo(NULL, kPortName, &hints, &ai);
	
	// Check errors to make sure we're ok so far
	if (rv)
	{
		error("getaddrinfo error: %s", gai_strerror(rv));
		return;
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
		
		int bindResult = bind(listeningSocket, p->ai_addr, p->ai_addrlen);
		if (bindResult < 0)
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
		error("Failed to bind to port %s", kPortName);
		return;
	}
	
	// No longer need ai struct pointer
	freeaddrinfo(ai);
	
	// Listen on port newly bound to our process
	int connectionBacklogSize = 10;
	if (listen(listeningSocket, connectionBacklogSize) == -1)
	{
		error("Listen failed.");
		return;
	}
	
	info("Listening on port: %s", kPortName);
	
	// Add the listener to the master set
	FD_SET(listeningSocket, &master_fds);
	
	// Keep track of the biggest file descriptor
	int largestFileDescriptor = listeningSocket;
	
	// Connecting client structures. Referred to in the following loop
	struct sockaddr_storage remoteAddress;
	socklen_t addressLength;
	int newFileDescriptor;
	char remoteIP[INET6_ADDRSTRLEN];
	
	WebSocketSession* session = NULL;
	
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
				// Handle a new connection
				addressLength = sizeof(remoteAddress);
				newFileDescriptor = accept(listeningSocket,
																	 (struct sockaddr*) &remoteAddress,
																	 &addressLength);
				
				// Error checking
				if (newFileDescriptor == -1)
				{
					error("accept() failed.");
					continue;
				}
				
				// Keep track of largest file descriptor
				FD_SET(newFileDescriptor, &master_fds);
				if (newFileDescriptor > largestFileDescriptor)
				{
					largestFileDescriptor = newFileDescriptor;
				}
				
				info("New connection from %s on socket %d",
						 inet_ntop(remoteAddress.ss_family,
											 get_in_addr(((struct sockaddr*)&remoteAddress)),
											 remoteIP,
											 INET6_ADDRSTRLEN),
						 newFileDescriptor);
				
				continue;
			}
			
			if (!session)
			{
				session = new WebSocketSession(i);
				session->init();
			} else {
				session->newData();
			}
			
			// Any number of interactions could have caused the session to close
			// so trap for all of them, even directly after init
			if (!session->open())
			{
				// Clean up session
				delete session;
				session = NULL;
				
				// Clean up socket
				close(i);
				FD_CLR(i, &master_fds);
			}
		}
	}
	
	info("Caught exit signal. Cleaning up.");
	
	// Clean up
	for (int i = 0; i <= largestFileDescriptor; i++)
	{
		close(i);
		FD_CLR(i, &master_fds);
	}
}

bool Server::init()
{
	info("Socket server initialization.");
	
	_shouldTerminateThread = false;
	
	// Test Base64 encode:
	const char* testMessage = "Hello, World.";
	int testSize = (int)strlen(testMessage);
	const char* testTarget = "SGVsbG8sIFdvcmxkLg==";
	char scratch[64];
	memset(scratch, 0, 64);
	base64Encode((const unsigned char*)testMessage, testSize, scratch);
	
	if (strcmp(scratch, testTarget))
	{
		error("Failed to correctly generate b64 string.");
		return false;
	}
	
	return true;
}

bool Server::run()
{
	std::thread t(Server::awaitConnection);
	t.detach();
	
	return true;
}
