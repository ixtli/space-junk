//
//  hud.cpp
//  SpaceJunk
//
//  Created by ixtli on 6/17/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "uiManager.h"

#include "hud.h"

HUD::HUD()

{}

HUD::~HUD()
{
	UIManager::getInstance()->removeLayer(&_colorLayer);
}

bool HUD::init()
{
	_colorLayer.init(100);
	UIManager::getInstance()->addLayer(&_colorLayer);
	
	return true;
}

