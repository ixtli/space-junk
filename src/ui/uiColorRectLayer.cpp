//
//  colorRectUILayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/31/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "uiColorRectLayer.h"

UIColorRectLayer::UIColorRectLayer() :

_layer()

{}

UIColorRectLayer::~UIColorRectLayer()
{
	
}

bool UIColorRectLayer::init(size_t initialCount)
{
	if (!_layer.init(0, 1, SOLID_QUAD_SHADER))
	{
		error("couldn't init layer.");
		return false;
	}
	
	// TODO: Remove temp data
	_r = _layer.newRect();
	_r->width(100);
	_r->height(50);
	_r->top(25);
	_r->left(25);
	_r->rgba(180, 90, 5, 128);
	_layer.updateRect(_r);
	_layer.commit();
	
	return true;
}

void UIColorRectLayer::update(sjtime_t dt)
{
	
}