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
	if (!_layer.init(_depth, initialCount, kShader))
	{
		error("couldn't init layer.");
		return false;
	}
	
	return true;
}

void UIColorRectLayer::randomRect()
{
	UIColorRectElement* _r = _layer.newRect();
	
	// This can happen for any number of reasons
	if (!_r) return;
	
	const Size2I bounds = Renderer::getInstance()->bounds();
	
	_r->width(RAND_UINT(50, 200));
	_r->height(RAND_UINT(50, 200));
	_r->top(RAND_UINT(0, bounds.height));
	_r->left(RAND_UINT(0, bounds.width));
	_r->rgba(RAND_BYTE(0, 255), RAND_BYTE(0, 255), RAND_BYTE(0, 255), 128);
	
}

void UIColorRectLayer::update(sj_time_t dt)
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
