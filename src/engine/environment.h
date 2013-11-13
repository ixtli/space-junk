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
	
	static void updateRenderables();
	static void render();
	static void viewResize(unsigned w, unsigned h);
	
	typedef enum
	{
		UI_ELEMENT,
		NUM_LOCKS
	} LockNames;
	
	static void releaseLock(LockNames name);
	static bool requestLock(LockNames name, bool wait);
	static bool waitOnLock(LockNames name, sjtime_t time);
	
private:
	
	Environment();
	~Environment();
	
	static Environment _instance;
	
};

#endif /* defined(__SpaceJunk__environment__) */
