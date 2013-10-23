//
//  engine.h
//  Space Junk
//
//  Created by ixtli on 5/8/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __Space_Junk__engine__
#define __Space_Junk__engine__

class HUD;

class Engine
{
public:
	
	inline static Engine* getInstance() { return &_instance; };
	
	bool init();
	void update(uint64_t dt);
	void setMaxFPS(time_t frameCount);
	
private:
	
	Engine();
	~Engine();
	
	static Engine _instance;
	
	HUD* _hud;
	
	uint64_t _previousUpdate;
	uint64_t _minClocksPerFrame;
	uint64_t _maxFPS;
};

#endif /* defined(__Space_Junk__engine__) */
