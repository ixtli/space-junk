//
//  quadLayer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/24/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "quadLayer.h"

QuadLayer::QuadLayer(bool dynamic) :

_dynamic(dynamic),
_maxQuads(0),
_usedQuads(0),
_shaderFormat(NUM_SHADER_TYPES)

{}

QuadLayer::~QuadLayer()
{
	
}

bool QuadLayer::init(GLuint maxQuads, ShaderFormat shader, const GLvoid* verts)
{
	if (!maxQuads)
	{
		error("Attempt to init with zero max quads.");
		return false;
	}
	
	_maxQuads = maxQuads;
	_usedQuads = maxQuads;
	_shaderFormat = shader;
	
	GLuint indexCount = _maxQuads * 6 - 2;
	
	// Construct some temp data
	GLushort* indicies = new GLushort[indexCount];
	
	generateElementIndicies(indicies);
	
	// Initialize a new trianglebuffer
	const TriangleBuffer::TriBufferConfig conf = {
		.dynamic = _dynamic,
		.vertexCount = _maxQuads * 4,
		.indexCount = indexCount,
		.indicies = indicies,
		.verticies = verts,
		.attrCount = ShaderFormats::definitions[shader].attrCount,
		.attributes = ShaderFormats::definitions[shader].attrs
	};
	
	// Construct buffer
	bool result = _buffer.init(conf);
	
	// Clean up
	delete [] indicies;

	return result;
}

/*
 Expects an array the size of _maxQuads * 6 - 2
 */
void QuadLayer::generateElementIndicies(GLushort *indicies)
{
	GLshort val = 0, index = 0;
	for (GLuint i = 0; i < _maxQuads; i++)
	{
		indicies[index] = val;
		indicies[index + 1] = val + 1;
		indicies[index + 2] = val + 2;
		indicies[index + 3] = val + 3;
		
		if (i + 1 < _maxQuads)
		{
			indicies[index + 4] = val + 3;
			indicies[index + 5] = val + 4;
		}
		
		val += 4;
		index += 6;
	}
}

void QuadLayer::usedQuads(GLuint used)
{
	if (_usedQuads >= _maxQuads) return;
	
	_usedQuads = used;
	_buffer.count(_usedQuads * 4);
}

bool QuadLayer::resizeLayer(GLuint newMaxQuads)
{
	_maxQuads = newMaxQuads;
	
//	GLuint indexCount = _maxQuads * 6 - 2;
	
	// TODO: resize
	
	return true;
}
