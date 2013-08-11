//
//  CubeManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 8/11/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "CubeManager.h"

CubeManager CubeManager::_instance;

CubeManager::CubeManager() :

_size(),
_buffer(),
_cubes(NULL)

{}

CubeManager::~CubeManager()
{
	if (_cubes) delete [] _cubes;
}

bool CubeManager::init(const Size3U &size, ShaderFormat format)
{
	_shaderFormat = format;
	_size.set(size);
	GLuint total = _size.volume();
	GLuint indexCount = INDICIES_PER_CUBE * total;
	GLuint vertexCount = VERTS_PER_CUBE * total;
	
	// Allocate and check
	_cubes = new Cube[total];
	if (!_cubes)
	{
		error("Couldn't allocate memory for cubes.");
		return false;
	}
	
	GLushort* indicies = new GLushort[indexCount];
	if (!indicies)
	{
		error("Couldn't allocate memory for indicies.");
		return false;
	}
	
	GLfloat* verts = new GLfloat[vertexCount];
	if (!verts)
	{
		error("Couldn't allocate memory for verts");
	}
	
	// Initialize
	for (GLuint i = 0; i < total; i++)
	{
		if (!_cubes[i].init())
		{
			error("Error initializing cube %u.", i);
			return false;
		}
	}
	
	// Initialize a new trianglebuffer
	const TriangleBuffer::TriBufferConfig conf = {
		.dynamic = false,
		.vertexCount = vertexCount,
		.indexCount = indexCount,
		.indicies = indicies,
		.verticies = verts,
		.attrCount = ShaderFormats::definitions[_shaderFormat].attrCount,
		.attributes = ShaderFormats::definitions[_shaderFormat].attrs
	};
	
	bool result = _buffer.init(conf);
	
	// Clean up
	delete [] indicies;
	delete [] verts;
	
	return result;
}


