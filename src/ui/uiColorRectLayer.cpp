//
//  colorRectUILayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/31/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "uiColorRectLayer.h"

UIColorRectLayer::UIColorRectLayer() :

UILayer(&_layer),
_r()

{}

UIColorRectLayer::~UIColorRectLayer()
{
	
}

bool UIColorRectLayer::init()
{
	// TODO: Remove temp data
	_r.width(27);
	_r.height(38);
	_r.left(10);
	_r.top(32);
	_r.rgba(180, 90, 5, 128);
	_layer.init(0, 1);
	_layer.addRect(_r.layerRect());
	_layer.commit();
	
	return true;
}