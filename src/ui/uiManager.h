//
//  uiManager.h
//  SpaceJunk
//
//  Created by ixtli on 5/21/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiManager__
#define __SpaceJunk__uiManager__

class UILayer;

class UIManager
{
public:
	
	static UIManager* getInstance() { return &_instance; };
	
	bool init();
	bool addLayer(UILayer* layer);
	bool removeLayer(const UILayer* layer);
	
	static void draw();
	static void update(time_t time);
	
private:
	
	UIManager();
	~UIManager();
	
	bool growLayerList();
	
	UILayer** _layers;
	size_t _maxLayers;
	size_t _layerCount;
	
	static UIManager _instance;
	
};

#endif /* defined(__SpaceJunk__uiManager__) */
