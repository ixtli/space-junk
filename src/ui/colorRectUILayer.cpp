//
//  colorRectUILayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/31/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "colorRectUILayer.h"

ColorRectUILayer::ColorRectUILayer() :

UILayer(&_layer)

{}

ColorRectUILayer::~ColorRectUILayer()
{
	
}

bool ColorRectUILayer::init()
{
	// TODO: Remove temp data
	_r.depthOffset = 0;
	_r.rect.bounds.width = 27;
	_r.rect.bounds.height = 38;
	_r.rect.position.x = 10;
	_r.rect.position.y = 32;
	_r.color.r = 180;
	_r.color.g = 90;
	_r.color.b = 5;
	_r.color.a = 200;
	
	_layer.init(0, 1);
	_layer.addRect(&_r);
	_layer.commit();
	
	return true;
}