//
//  uiLayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/30/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "uiLayer.h"

UILayer::UILayer(RectLayer* layer) :

_layer(layer),
_elementCount(0),
_elementList(NULL)

{}

UILayer::~UILayer()
{
	if (_elementList) delete [] _elementList;
}

void UILayer::update(sjtime_t dt)
{
	for (size_t i = 0; i < _elementCount; i++)
		_elementList[i]->update(dt);
}

void UILayer::depth(uint32_t d)
{
	// @TODO: Update all the elements in the layer
	_depth = d;
}

