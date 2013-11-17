//
//  uiManager.h
//  SpaceJunk
//
//  Created by ixtli on 5/21/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiManager__
#define __SpaceJunk__uiManager__

#include "IComponent.h"

#include "geometry.h"

class UILayer;
class HUD;

/**
 Manages the user interface layer which is drawn on top of the scene
 */
class UIManager : public IComponent
{
public:
	
	/** @return the singleton instance of the class */
	static UIManager* getInstance() { return &_instance; };
	
	// IComponent functionality
	virtual bool init();
	virtual void update(sjtime_t dt);
	
	void viewDidResize(const Size2I &bounds);
	bool addLayer(UILayer* layer);
	bool removeLayer(const UILayer* layer);
	
	static void draw();
	
private:
	
	UIManager();
	virtual ~UIManager();
	
	bool growLayerList();
	
	UILayer** _layers;
	size_t _maxLayers;
	size_t _layerCount;
	
	/** Singleton instance */
	static UIManager _instance;
	
	// @TODO: Do something with this
	HUD* h;
	
};

#endif /* defined(__SpaceJunk__uiManager__) */
