//
//  engine.h
//  Space Junk
//
//  Created by ixtli on 5/8/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __Space_Junk__engine__
#define __Space_Junk__engine__

class Engine
{
public:
	
	/** @return a pointer to the singleton instance */
	inline static Engine* getInstance() { return &_instance; };
	
	// IComponent functionality
	bool init();
	void update(sjtime_t now);
	
private:
	
	Engine();
	~Engine();
	
	static Engine _instance;
	
	bool initComponents();
	
	sjtime_t _lastUpdate;
};

#endif /* defined(__Space_Junk__engine__) */

