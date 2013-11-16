//
//  uiColorRectElement.cpp
//  SpaceJunk
//
//  Created by Ixtli on 6/2/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "vertexFormats.h"
#include "uiColorRectElement.h"

UIColorRectElement::UIColorRectElement() :

UIElement(),
_color()

{}

UIColorRectElement& UIColorRectElement::operator=(const UIColorRectElement &c)
{
	UIElement::operator=(c);
	
	_color = c._color;
	
	return *this;
}

UIColorRectElement::~UIColorRectElement()
{
	
}

void UIColorRectElement::rgba(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	red(r);
	green(g);
	blue(b);
	alpha(a);
}

void UIColorRectElement::updateVerts(GLfloat baseDepth, ColorVertex* verts) const
{
	size_t v = _index * 4;
	
	// Bottom left
	verts[v].location.x = _rect.position.x;
	verts[v].location.y = _rect.position.y + _rect.bounds.height;
	
	verts[v].location.z = baseDepth + _depthOffset;
	verts[v++].color = _color;
	
	// Bottom Right
	verts[v].location.x = _rect.position.x + _rect.bounds.width;
	verts[v].location.y = _rect.position.y + _rect.bounds.height;
	
	verts[v].location.z = baseDepth + _depthOffset;
	verts[v++].color = _color;
	
	// Top Left
	verts[v].location.x = _rect.position.x;
	verts[v].location.y = _rect.position.y;
	
	verts[v].location.z = baseDepth + _depthOffset;
	verts[v++].color = _color;
	
	// Top Right
	verts[v].location.x = _rect.position.x + _rect.bounds.width;
	verts[v].location.y = _rect.position.y;
	
	verts[v].location.z = baseDepth + _depthOffset;
	verts[v++].color = _color;
}
