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
	if (!_layer.init(_depth, initialCount, SOLID_QUAD_SHADER))
	{
		error("couldn't init layer.");
		return false;
	}
	
	return true;
}

void UIColorRectLayer::randomRect()
{
	UIColorRectElement* _r = _layer.newRect();
	
	const Size2I bounds = Renderer::getInstance()->bounds();
	
	_r->width(RAND_BETWEEN(50, 200));
	_r->height(RAND_BETWEEN(50, 200));
	_r->top(RAND_BELOW(bounds.height));
	_r->left(RAND_BELOW(bounds.width));
	_r->rgba(RAND_BELOW(255), RAND_BELOW(255), RAND_BELOW(255), 128);
}

void UIColorRectLayer::update(sjtime_t dt)
{
	GLuint count = _layer.used();
	
	for (GLuint i = 0; i < count; i++)
	{
		if (_layer.rectForIndex(i)->dirty())
			_layer.updateRect(_layer.rectForIndex(i));
	}
	
	_layer.commit();
}

UIColorRectElement* UIColorRectLayer::newElement()
{
	return _layer.newRect();
}

void UIColorRectLayer::removeElement(UIColorRectElement *e)
{
	_layer.removeRect(e);
}