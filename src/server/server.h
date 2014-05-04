//
//  server.h
//  SpaceJunk
//
//  Created by ixtli on 5/1/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__server__
#define __SpaceJunk__server__

class Server
{
public:

	inline static Server* getInstance() { return &_instance; };
	
	bool init();
	bool run();
	
private:
	
	Server();
	~Server();
	
	static Server _instance;
	
	static bool _shouldTerminateThread;
	
	static void* get_in_addr(struct sockaddr* sa);
	static void awaitConnection();
	
};

#endif /* defined(__SpaceJunk__server__) */
