//
//  uiElement.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/31/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "uiElement.h"

UIElement::UIElement() :

_rect(),
_depth(0)

{}

UIElement::UIElement(const RectI& rect) :

_rect(rect),
_depth(0)

{}

UIElement::UIElement(const RectI& rect, GLfloat depth) :

_rect(rect),
_depth(depth)

{}

UIElement::~UIElement()
{
    
}