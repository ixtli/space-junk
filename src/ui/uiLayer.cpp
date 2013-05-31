//
//  uiLayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/30/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "uiLayer.h"

UILayer::UILayer() :

_elementCount(0)

{}

UILayer::~UILayer()
{
	
}

bool UILayer::init(unsigned int elementCount)
{
	_elementCount = elementCount;
	
	return true;
}

