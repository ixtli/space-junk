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
_depthOffset(0),
_dirty(true)

{}

UIElement& UIElement::operator=(const UIElement &e)
{
	_rect = e._rect;
	_index = e._index;
	_depthOffset = e._depthOffset;
	_dirty = e._dirty;
	
	return *this;
}

UIElement::~UIElement()
{
    
}
