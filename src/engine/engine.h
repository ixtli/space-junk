//
//  engine.h
//  Space Junk
//
//  Created by ixtli on 5/8/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __Space_Junk__engine__
#define __Space_Junk__engine__

#include "IComponent.h"

class HUD;

class Engine : public IComponent
{
public:
	
	/** @return a pointer to the singleton instance */
	inline static Engine* getInstance() { return &_instance; };
	
	// IComponent functionality
	virtual bool init();
	virtual void update(uint32_t now);
	
private:
	
	Engine();
	virtual ~Engine();
	
	static Engine _instance;
	
	typedef enum
	{
		UI_MANAGER,
		CUBE_MANAGER,
		JS_MANAGER,
		NUM_COMPONENTS
	} ComponentList;
	
	IComponent* _components[NUM_COMPONENTS];
	
	bool initComponents();
	
	uint32_t _lastUpdate;
	
	HUD* _hud;
};

#endif /* defined(__Space_Junk__engine__) */
