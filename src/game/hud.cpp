//
//  hud.cpp
//  SpaceJunk
//
//  Created by ixtli on 6/17/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "colorRectUILayer.h"
#include "uiManager.h"

#include "hud.h"

HUD::HUD() :

_colorLayer(NULL)

{}

HUD::~HUD()
{
	if (_colorLayer)
	{
		UIManager::getInstance()->removeLayer(_colorLayer);
		delete _colorLayer;
	}
}

bool HUD::init()
{
	_colorLayer = new ColorRectUILayer();
	_colorLayer->init();
	UIManager::getInstance()->addLayer(_colorLayer);
	
	return true;
}

