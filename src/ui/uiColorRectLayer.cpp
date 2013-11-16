//
//  colorRectUILayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/31/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "randUtil.h"

#include "uiColorRectLayer.h"

UIColorRectLayer::UIColorRectLayer() :

_layer()

{}

UIColorRectLayer::~UIColorRectLayer()
{
	
}

bool UIColorRectLayer::init(size_t initialCount)
{
	if (!_layer.init(0, 5, SOLID_QUAD_SHADER))
	{
		error("couldn't init layer.");
		return false;
	}
	
	randomRect();
	randomRect();
	randomRect();
	randomRect();
	randomRect();
	
	_layer.commit();
	
	return true;
}

void UIColorRectLayer::randomRect()
{
	// TODO: Remove temp data
	UIColorRectElement* _r = _layer.newRect();
	_r->width(RAND_BETWEEN(50, 200));
	_r->height(RAND_BETWEEN(50, 200));
	_r->top(RAND_BETWEEN(100, 300));
	_r->left(RAND_BETWEEN(100, 300));
	_r->rgba(RAND_BELOW(255), RAND_BELOW(255), RAND_BELOW(255), 128);
	_layer.updateRect(_r);
}

void UIColorRectLayer::update(sjtime_t dt)
{
	GLuint idx = RAND_BELOW(5);
	UIColorRectElement* _r = _layer.rectForIndex(idx);
	_r->rgba(RAND_BELOW(255), RAND_BELOW(255), RAND_BELOW(255), 128);
	_layer.updateRect(_r);
	
	
	_layer.commit();
}