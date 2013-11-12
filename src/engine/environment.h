//
//  environment.h
//  SpaceJunk
//
//  Created by ixtli on 5/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__environment__
#define __SpaceJunk__environment__

#include <stdlib.h>

class Environment
{
public:
	
	bool init();
	
	// Static functionality
	inline static Environment* getInstance() { return &_instance; };
	static char* newPathForFile(const char* name, const char* type);
	static sjtime_t currentTime();
	static void updateGameEvent(void* ctx);
	static void render();
	static void viewResize(unsigned w, unsigned h);
	
private:
	
	Environment();
	~Environment();
	
	static Environment _instance;
	
};

#endif /* defined(__SpaceJunk__environment__) */
