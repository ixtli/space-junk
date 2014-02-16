//
//  configuration.h
//  SpaceJunk
//
//  Created by ixtli on 12/23/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__configuration__
#define __SpaceJunk__configuration__

class Configuration
{
public:
	
	inline static Configuration* getInstance() { return &_instance; };
	
	unsigned int _serverPort;
	
private:
	
	Configuration();
	~Configuration();
	
	static Configuration _instance;
	
};

#endif /* defined(__SpaceJunk__configuration__) */
