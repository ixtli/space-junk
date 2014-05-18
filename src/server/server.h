//
//  server.h
//  SpaceJunk
//
//  Created by ixtli on 5/1/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__server__
#define __SpaceJunk__server__

#include "uthash.h"

class WebSocketSession;

class Server
{
public:

	inline static Server* getInstance() { return &_instance; };
	
	bool init();
	bool run(unsigned int port);
	bool stop();
	
	bool isRunning() const;
	
private:
	
	Server();
	~Server();
	
	typedef struct
	{
		WebSocketSession* session;
		int fileDescriptor;
		UT_hash_handle hh;
	} OpenSession;
	
	unsigned int _listeningPort;
	
	static Server _instance;
	static bool _shouldTerminateThread;
	
	static void* get_in_addr(struct sockaddr* sa);
	static int listenForConnections(unsigned int port);
	static void awaitConnection(int listeningSocket);
	static int acceptConnection(int acceptingSocket);
	static int openConnection(const char* host, unsigned int port);
	
};

#endif /* defined(__SpaceJunk__server__) */
