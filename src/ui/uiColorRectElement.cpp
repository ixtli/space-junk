//
//  uiColorRectElement.cpp
//  SpaceJunk
//
//  Created by Ixtli on 6/2/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "uiColorRectElement.h"

ColorRectUIElement::ColorRectUIElement() :

UIElement(),
_color(),
_layerRect(&_rect, &_color, _depth)

{}

ColorRectUIElement::ColorRectUIElement(const RectI& rect, GLfloat depth) :

UIElement(rect),
_color(),
_layerRect(&_rect, &_color, _depth)

{}

ColorRectUIElement::ColorRectUIElement(const RectI& rect,
																			 const Color4u& c,
																			 GLfloat depth) :

UIElement(rect),
_color(c),
_layerRect(&_rect, &_color, _depth)

{}

ColorRectUIElement::~ColorRectUIElement()
{
	
}

void ColorRectUIElement::rgba(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	_color.r = r;
	_color.g = g;
	_color.b = b;
	_color.a = a;
}