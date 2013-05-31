//
//  rectLayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/30/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "rectLayer.h"

RectLayer::RectLayer(bool dynamic) :

_quadLayer(dynamic),
_maxRects(0),
_usedRects(0),
_depth(0.0f)

{}

RectLayer::~RectLayer()
{
	
}

bool RectLayer::init(GLfloat depth, GLuint rectCount)
{
	
	if (!rectCount)
	{
		error("Must initialize layer with at least one rect.");
		return false;
	}
	
	if (rectCount >= MAX_RECTS)
	{
		error("A single layer can't have more than %u rects.", MAX_RECTS);
		return false;
	}
	
	_depth = depth;
	_maxRects = rectCount;
	
	return true;
}