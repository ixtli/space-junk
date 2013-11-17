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
	_elt = _colorLayer.newElement();
	
	_elt->width(50);
	_elt->height(50);
	_elt->left(150);
	_elt->top(100);
	_elt->rgba(255, 0, 0, 128);
	
	_easer.init(1000);
	_easer.setStart(150);
	_easer.setDistance(500);
	_easer.restart();
	UIManager::getInstance()->addLayer(&_colorLayer);
	
	return true;
}

void HUD::update(sjtime_t dt)
{
	if (_easer.isComplete()) return;
	
	_elt->left(_easer.update(dt));
}