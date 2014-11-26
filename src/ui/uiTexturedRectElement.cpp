//
//  uiTexturedRectElement.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/25/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "uiTexturedRectElement.h"

UITexturedRectElement::UITexturedRectElement() :

_texCoord()

{}

void UITexturedRectElement::uv(float _u, float _v)
{
	_texCoord.x = _u;
	_texCoord.y = _v;
}

void UITexturedRectElement::updateVerts(GLfloat depth, TextureVertex *verts) const
{
	size_t v = _index * 4;
	
	// Bottom left
	verts[v].location.x = _rect.position.x;
	verts[v].location.y = _rect.position.y + _rect.bounds.height;
	verts[v].location.z = depth;
	
	verts[v].texCoord.x = _texCoord.x;
	verts[v].texCoord.y = _texCoord.y + _texSize.y;
	
	v++;
	
	// Bottom Right
	verts[v].location.x = _rect.position.x + _rect.bounds.width;
	verts[v].location.y = _rect.position.y + _rect.bounds.height;
	verts[v].location.z = depth;
	
	verts[v].texCoord.x = _texCoord.x + _texSize.x;
	verts[v].texCoord.y = _texCoord.y + _texSize.y;

	
	v++;
	
	// Top Left
	verts[v].location.x = _rect.position.x;
	verts[v].location.y = _rect.position.y;
	verts[v].location.z = depth;
	
	verts[v].texCoord.x = _texCoord.x;
	verts[v].texCoord.y = _texCoord.y;
	
	v++;
	
	// Top Right
	verts[v].location.x = _rect.position.x + _rect.bounds.width;
	verts[v].location.y = _rect.position.y;
	verts[v].location.z = depth;
	
	verts[v].texCoord.x = _texCoord.x + _texSize.x;
	verts[v].texCoord.y = _texCoord.y;
}
