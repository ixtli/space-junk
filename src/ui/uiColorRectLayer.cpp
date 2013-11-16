//
//  colorRectUILayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/31/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "randUtil.h"
#include "renderer.h"
#include "uiColorRectLayer.h"

UIColorRectLayer::UIColorRectLayer() :

_layer()

{}

UIColorRectLayer::~UIColorRectLayer()
{
	
}

bool UIColorRectLayer::init(uint32_t initialCount)
{
	
	if (!_layer.init(0, initialCount, SOLID_QUAD_SHADER))
	{
		error("couldn't init layer.");
		return false;
	}
	
	return true;
}

void UIColorRectLayer::randomRect()
{
	// TODO: Remove temp data
	UIColorRectElement* _r = _layer.newRect();
	
	const Size2I bounds = Renderer::getInstance()->bounds();
	
	_r->width(RAND_BETWEEN(50, 200));
	_r->height(RAND_BETWEEN(50, 200));
	_r->top(RAND_BELOW(bounds.height));
	_r->left(RAND_BELOW(bounds.width));
	_r->rgba(RAND_BELOW(255), RAND_BELOW(255), RAND_BELOW(255), 128);
	
	_layer.updateRect(_r);
}

void UIColorRectLayer::update(sjtime_t dt)
{
	GLuint idx = RAND_BELOW(_layer.maxRects());
	
	if (idx >= _layer.used())
	{
		randomRect();
	} else {
		_layer.removeRect(_layer.rectForIndex(idx));
	}
	
	_layer.commit();
}