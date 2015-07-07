//
//  uiTexturedRectLayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/26/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "randUtil.h"

#include "uiTexturedRectLayer.h"

#include "environment.h"
#include "pngUtil.h"

UITexturedRectLayer::UITexturedRectLayer() :

_layer(),
_texture(),
_stringTexture(),
_stringHeight(0),
_samplerLocation(-1)

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

	ShaderManager::use(kShader);
	PNGWrapper png;
	png.init("grass");
	_texture.init(png.width(), png.height(), png.data());
	_samplerLocation = ShaderManager::getUniformLocation("sampler");
	
	// Init texture for string
	const char* tmp = "This is a string that i'd like to use to test rendering.";
	constexpr float width = 300.0f;
	_stringHeight = Environment::getHeightOfStringWithWidth(tmp, width);
	_stringHeight = ceilf(_stringHeight) + 20;
	
	unsigned char* buff = new unsigned char[(size_t)(width * _stringHeight) * 4];
	Environment::renderString(tmp, buff, width, _stringHeight);
	_stringTexture.init((GLsizei)width, (GLsizei)_stringHeight, buff);
	delete [] buff;
	
	return true;
}

void UITexturedRectLayer::randomRect()
{
	UITexturedRectElement* _r = _layer.newRect();
	
	if (!_r) return;
	
	const Size2I bounds = Renderer::getInstance()->bounds();
	
	_r->width(32);
	_r->height(32);
	_r->top(RAND_UINT(0, bounds.height));
	_r->left(RAND_UINT(0, bounds.width));
	
	float texSize = 1.0f;
	
	_r->uv(0, 0);
	_r->textureHeight(texSize);
	_r->textureWidth(texSize);
	
	showText();
}

void UITexturedRectLayer::showText()
{
	UITexturedRectElement* _r = _layer.newRect();
	
	if (!_r) return;
	
	_r->height((GLint)_stringHeight);
	_r->width(300);
	_r->top(25);
	_r->left(25);
	_r->uv(0, 0);
	constexpr float texSize = 1.0f;
	_r->textureHeight(texSize);
	_r->textureWidth(texSize);
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
