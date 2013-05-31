//
//  uiLayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/30/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "uiLayer.h"

UILayer::UILayer(const RectLayer* layer) :

_layer(layer),
_elementCount(0),
_elementList(NULL)

{}

UILayer::~UILayer()
{
	if (_elementList) delete [] _elementList;
}


