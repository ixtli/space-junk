//
//  engine.h
//  Space Junk
//
//  Created by ixtli on 5/8/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __Space_Junk__engine__
#define __Space_Junk__engine__

#include "../util/chronoUtil.h"

class Engine
{
public:
	
	/** @return a pointer to the singleton instance */
	inline static Engine* getInstance() { return &_instance; };
	
	// IComponent functionality
	bool init();
	void destroy();
	void update(sj_time_t dt);
	bool isRunning() const;
	
private:
	
	Engine();
	~Engine();
	
	static Engine _instance;
	
	bool initComponents();
	void threadMain();
	static bool _shouldTerminate;
};

#endif /* defined(__Space_Junk__engine__) */

