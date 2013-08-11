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
	void update();
	
private:
	
	Engine();
	~Engine();
	
	static Engine _instance;
	
	HUD* _hud;
	
};

#endif /* defined(__Space_Junk__engine__) */
