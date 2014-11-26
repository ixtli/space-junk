//
//  uiTexturedRectLayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/26/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "randUtil.h"

#include "uiTexturedRectLayer.h"

#include "pngUtil.h"

UITexturedRectLayer::UITexturedRectLayer() :

_layer()

{}

UITexturedRectLayer::~UITexturedRectLayer()
{
	
}

bool UITexturedRectLayer::init(uint32_t initialCount)
{
	if (!_layer.init(_depth, initialCount, kShader))
	{
		error("Couldn't init layer.");
		return false;
	}
	
	PNGWrapper png;
	png.init("grass");
	_texture.init(png.width(), png.height(), png.data());
	
	return true;
}

void UITexturedRectLayer::randomRect()
{
	UITexturedRectElement* _r = _layer.newRect();
	
	if (!_r) return;
	
	const Size2I bounds = Renderer::getInstance()->bounds();
	
	_r->width(RAND_UINT(50, 200));
	_r->width(RAND_UINT(50, 200));
	_r->height(RAND_UINT(50, 200));
	_r->top(RAND_UINT(0, bounds.height));
	_r->left(RAND_UINT(0, bounds.width));
	
	_r->uv(0, 0);
	_r->textureHeight(1.0f);
	_r->textureWidth(1.0f);
}

void UITexturedRectLayer::update(sj_time_t dt)
{
	GLuint count = _layer.used();
	
	for (GLuint i = 0; i < count; i++)
	{
		if (_layer.rectForIndex(i)->dirty())
			_layer.updateRect(_layer.rectForIndex(i));
	}
	
	_layer.commit();
}

UITexturedRectElement* UITexturedRectLayer::newElement()
{
	return _layer.newRect();
}

void UITexturedRectLayer::removeElement(UITexturedRectElement *e)
{
	_layer.removeRect(e);
}
