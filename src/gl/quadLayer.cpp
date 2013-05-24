//
//  quadLayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/24/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "quadLayer.h"

QuadLayer::QuadLayer() :

_maxQuads(0),
_shaderFormat(NUM_SHADER_TYPES)

{}

QuadLayer::~QuadLayer()
{
	
}

bool QuadLayer::init(GLuint maxQuads, ShaderFormat shaderFormat)
{
	if (!maxQuads)
	{
		error("Attempt to init with zero max quads.");
		return false;
	}
	
	_maxQuads = maxQuads;
	_shaderFormat = shaderFormat;
	
	// Construct some temp data
	static const GLfloat size = 100.0f;
	static const GLushort indicies[] = {0, 1, 2, 3};
	static const ColorVertex verts[] = {
		{
			// Bottom left
			.location = Point3Df(0, size, 0),
			.color = Color4u(100, 0, 0, 255)
		},
		{
			// Bottom right
			.location = Point3Df(size, size, 0),
			.color = Color4u(100, 0, 0, 255)
		},
		{
			// Top left
			.location = Point3Df(0, 0, 0),
			.color = Color4u(100, 0, 0, 255)
		},
		{
			// Top right
			.location = Point3Df(size, 0, 0),
			.color = Color4u(100, 0, 0, 255)
		},
	};
	
	// Initialize a new trianglebuffer
	static const TriangleBuffer::TriBufferConfig conf = {
		.dynamic = false,
		.vertexCount = 4,
		.indexCount = 4,
		.attrCount = 2,
		.indicies = indicies,
		.verticies = verts,
		.attributes = VertexFormats::solidQuadList
	};
	
	// Construct buffer
	if (!_buffer.init(conf)) return false;
	
	return true;
}