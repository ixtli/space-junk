//
//  triangleBuffer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/20/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "triangleBuffer.h"

TriangleBuffer::TriangleBuffer() :

_dynamic(GL_TRUE),
_vertexAttrs(NULL),
_attrCount(0),
_vertexCount(0)

{ }

TriangleBuffer::~TriangleBuffer()
{
	
}

bool TriangleBuffer::init(bool dynamic,
													GLuint attrCount,
													const VertexAttribute **attrs)
{
	_dynamic = dynamic;
	_vertexAttrs = attrs;
	
	log("Initializing triangle buffer with %s", _vertexAttrs[0]->name);
	
	return true;
}