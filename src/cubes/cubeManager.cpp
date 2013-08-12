//
//  CubeManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 8/11/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "glutil.h"
#include "shaderManager.h"
#include "CubeManager.h"

CubeManager CubeManager::_instance;

CubeManager::CubeManager() :

_size(),
_buffer(),
_cubes(NULL),
_verts(NULL),
_indicies(NULL)

{}

CubeManager::~CubeManager()
{
	if (_cubes) delete [] _cubes;
	if (_verts) delete [] _verts;
	if (_indicies) delete [] _indicies;
}

bool CubeManager::init(const Size3U &size, ShaderFormat format)
{
	_shaderFormat = format;
	_size.set(size);
	GLuint total = _size.volume();
	GLuint indexCount = INDICIES_PER_CUBE * total;
	GLuint vertexCount = VERTS_PER_CUBE * total;
	
	info("Initializing %i cubes.", total);
	
	// Allocate and check
	_cubes = new Cube[total];
	if (!_cubes)
	{
		error("Couldn't allocate memory for cubes.");
		return false;
	}
	
	_indicies = new GLushort[indexCount];
	if (!_indicies)
	{
		error("Couldn't allocate memory for indicies.");
		return false;
	}
	
	_verts = new ColorVertex[vertexCount];
	if (!_verts)
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
	
	generateElementIndicies(_indicies);
	
	generateVertsFromCubes(_verts);
	
	// Initialize a new trianglebuffer
	const TriangleBuffer::TriBufferConfig conf = {
		.dynamic = false,
		.vertexCount = vertexCount,
		.indexCount = indexCount,
		.indicies = _indicies,
		.verticies = _verts,
		.attrCount = ShaderFormats::definitions[_shaderFormat].attrCount,
		.attributes = ShaderFormats::definitions[_shaderFormat].attrs
	};
	
	bool result = _buffer.init(conf);
	
	return result;
}

// Inline render functions
void CubeManager::draw()
{
	ShaderManager::use(_instance._shaderFormat);
	_instance._buffer.draw();
	GetGLError();
};

void CubeManager::generateElementIndicies(GLushort* indicies)
{
	GLuint total = _size.volume();
	for (GLushort i = 0; i < total; i += INDICIES_PER_CUBE)
	{
		// front
		indicies[i + 0] = i + 0;
		indicies[i + 1] = i + 1;
		indicies[i + 2] = i + 2;
		indicies[i + 3] = i + 2;
		indicies[i + 4] = i + 3;
		indicies[i + 5] = i + 0;
		
		// top
		indicies[i + 6] = i + 3;
		indicies[i + 7] = i + 2;
		indicies[i + 8] = i + 6;
		indicies[i + 9] = i + 6;
		indicies[i + 10] = i + 7;
		indicies[i + 11] = i + 3;
		
		// back
		indicies[i + 12] = i + 7;
		indicies[i + 13] = i + 6;
		indicies[i + 14] = i + 5;
		indicies[i + 15] = i + 5;
		indicies[i + 16] = i + 4;
		indicies[i + 17] = i + 7;
		
		// bottom
		indicies[i + 18] = i + 4;
		indicies[i + 19] = i + 5;
		indicies[i + 20] = i + 1;
		indicies[i + 21] = i + 1;
		indicies[i + 22] = i + 0;
		indicies[i + 23] = i + 4;
		
		// left
		indicies[i + 24] = i + 4;
		indicies[i + 25] = i + 0;
		indicies[i + 26] = i + 3;
		indicies[i + 27] = i + 3;
		indicies[i + 28] = i + 7;
		indicies[i + 29] = i + 4;
		
		// right
		indicies[i + 30] = i + 1;
		indicies[i + 31] = i + 5;
		indicies[i + 32] = i + 6;
		indicies[i + 33] = i + 6;
		indicies[i + 34] = i + 2;
		indicies[i + 35] = i + 1;
	}
}

void CubeManager::generateVertsFromCubes(ColorVertex* verts)
{
	static const Point3F pts[VERTS_PER_CUBE] =
	{
		// Front
//		Point3F(150.0f, 150.0f,  0.5),
//		Point3F(200.0f, 150.0f,  0.5),
//		Point3F(200.0f, 200.0f,  0.5),
//		Point3F(150.0f, 200.0f,  0.5),
//		
//		// Back
//		Point3F(150.0f, 150.0f, -0.5),
//		Point3F(200.0f, 150.0f, -0.5),
//		Point3F(200.0f, 200.0f, -0.5),
//		Point3F(150.0f, 200.0f, -0.5)
		Point3F(-1.0f, -1.0f,  1.0f),
		Point3F( 1.0f, -1.0f,  1.0f),
		Point3F( 1.0f,  1.0f,  1.0f),
		Point3F(-1.0f,  1.0f,  1.0f),
		
		// Back
		Point3F(-1.0f, -1.0f, -1.0f),
		Point3F( 1.0f, -1.0f, -1.0f),
		Point3F( 1.0f,  1.0f, -1.0f),
		Point3F(-1.0f,  1.0f, -1.0f)
	};
	
	static const Color4u colors[VERTS_PER_CUBE] =
	{
		Color4u(255, 0, 0, 255),
		Color4u(0, 255, 0, 255),
		Color4u(0, 255, 255, 255),
		Color4u(255, 0, 0, 255),
		Color4u(0, 0, 255, 255),
		Color4u(255, 0, 0, 255),
		Color4u(255, 255, 0, 255),
		Color4u(255, 0, 255, 255)
	};
	
	GLuint total = _size.volume();
	GLuint idx = 0;
	
	for (GLuint i = 0; i < total; i++)
	{
		for (GLuint j = 0; j < VERTS_PER_CUBE; j++, idx++)
		{
			verts[idx].location.set(pts[j]);
			verts[idx].color.set(colors[j]);
		}
	}
}

