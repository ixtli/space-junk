//
//  uiManager.h
//  SpaceJunk
//
//  Created by ixtli on 5/21/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiManager__
#define __SpaceJunk__uiManager__

#include "chronoUtil.h"

#include "simpleVector.h"
#include "geometry.h"

class UILayer;

class UITexturedRectLayer;

/**
 Manages the user interface layer which is drawn on top of the scene
 */
class UIManager
{
public:
	
	/** @return the singleton instance of the class */
	static UIManager* getInstance() { return &_instance; };
	
	bool init();
	void update(sj_time_t dt);
	
	void viewDidResize(const Size2I &bounds);
	bool addLayer(UILayer* layer);
	bool removeLayer(UILayer* const layer);
	
	void makeRandomRect();
	
	static void draw();
	
private:
	
	UIManager();
	~UIManager();
	
	SimpleVector<UILayer*, true> _layers;
	
	UITexturedRectLayer* _randomRectLayer;
	
	/** Singleton instance */
	static UIManager _instance;
	
};

#endif /* defined(__SpaceJunk__uiManager__) */
