//
//  CubeManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 8/11/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

// Uncomment to debug indicies
// #define PRINT_INDICIES

#ifdef PRINT_INDICIES
#include <stdio.h>
#endif

#include "easing.h"

#include "CubeManager.h"

#include "pngUtil.h"
#include "texture.h"
Texture t;

CubeManager CubeManager::_instance;

CubeManager::CubeManager() :

_size(),
_buffer(),
_cubes(NULL),
_verts(NULL),
_indicies(NULL),
_camera(),
_shaderFormat(SOLID_CUBE_SHADER)

{}

CubeManager::~CubeManager()
{
	if (_cubes) delete [] _cubes;
	if (_verts) delete [] _verts;
	if (_indicies) delete [] _indicies;
}

bool CubeManager::init()
{
	const Size3U mapSize(2, 3, 2);
	
	_size.set(mapSize);
	GLuint total = _size.volume();
	GLuint indexCount = INDICIES_PER_CUBE * total - 2;
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
	
	// TODO: Do something fun with this
	// Initialize cubes
	GLuint i = 0;
	for (GLuint x = 0; x < _size.width; x++)
	{
		for (GLuint y = 0; y < _size.height; y++)
		{
			for (GLuint z = 0; z < _size.depth; z++)
			{
				if (!_cubes[i].init())
				{
					error("Error initializing cube %u.", i);
					return false;
				}
				
				_cubes[i].x(x + (.05f * i));
				_cubes[i].y(y + (.05f * i));
				_cubes[i].z(z + (.05f * i));
				
				i++;
			}
		}
	}
	
	// Initialize camera
	_camera.init();
	_camera.rotate(45.0f, 5000);
	
	// Make indicies and verts from generated cubes
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
	
	// Initialize the buffer and return status
	return _buffer.init(conf);
}

void CubeManager::viewDidResize(const Size2I &bounds)
{
	_camera.updateScreenBounds(bounds);
}

void CubeManager::draw()
{
	ShaderManager::use(_instance._shaderFormat);
	ShaderManager::getInstance()->setMVP(_instance._camera.getMatrix(),
																			 _instance._shaderFormat);
	
	t.bind();

	_instance._buffer.draw();
	GetGLError();
}

// Engine update function
void CubeManager::update(sj_time_t dt)
{
	_camera.update(dt);
}

void CubeManager::generateElementIndicies(GLushort* indicies)
{
	GLuint total = _size.volume();
	GLuint index = 0;
	GLushort val = 0;
	
#ifdef PRINT_INDICIES
	GLuint j = 0;
#endif
	
	for (GLushort i = 0; i < total; i++)
	{
		// front
		indicies[index + 0] = val + 0;
		indicies[index + 1] = val + 1;
		indicies[index + 2] = val + 2;
		indicies[index + 3] = val + 2;
		indicies[index + 4] = val + 3;
		indicies[index + 5] = val + 0;
		
#ifdef PRINT_INDICIES
		printf("%i, %i, %i, \n", indicies[j + 0], indicies[j + 1], indicies[j + 2]);
		printf("%i, %i, %i\n\n", indicies[j + 3], indicies[j + 4], indicies[j + 5]);
		j+=6;
#endif
		
		// top
		indicies[index + 6] = val + 3;
		indicies[index + 7] = val + 2;
		indicies[index + 8] = val + 6;
		indicies[index + 9] = val + 6;
		indicies[index + 10] = val + 7;
		indicies[index + 11] = val + 3;
		
#ifdef PRINT_INDICIES
		printf("%i, %i, %i, \n", indicies[j + 0], indicies[j + 1], indicies[j + 2]);
		printf("%i, %i, %i\n\n", indicies[j + 3], indicies[j + 4], indicies[j + 5]);
		j+=6;
#endif
		
		// back
		indicies[index + 12] = val + 7;
		indicies[index + 13] = val + 6;
		indicies[index + 14] = val + 5;
		indicies[index + 15] = val + 5;
		indicies[index + 16] = val + 4;
		indicies[index + 17] = val + 7;
		
#ifdef PRINT_INDICIES
		printf("%i, %i, %i, \n", indicies[j + 0], indicies[j + 1], indicies[j + 2]);
		printf("%i, %i, %i\n\n", indicies[j + 3], indicies[j + 4], indicies[j + 5]);
		j+=6;
#endif
		
		// bottom
		indicies[index + 18] = val + 4;
		indicies[index + 19] = val + 5;
		indicies[index + 20] = val + 1;
		indicies[index + 21] = val + 1;
		indicies[index + 22] = val + 0;
		indicies[index + 23] = val + 4;
		
#ifdef PRINT_INDICIES
		printf("%i, %i, %i, \n", indicies[j + 0], indicies[j + 1], indicies[j + 2]);
		printf("%i, %i, %i\n\n", indicies[j + 3], indicies[j + 4], indicies[j + 5]);
		j+=6;
#endif
		
		// left
		indicies[index + 24] = val + 4;
		indicies[index + 25] = val + 0;
		indicies[index + 26] = val + 3;
		indicies[index + 27] = val + 3;
		indicies[index + 28] = val + 7;
		indicies[index + 29] = val + 4;
		
#ifdef PRINT_INDICIES
		printf("%i, %i, %i, \n", indicies[j + 0], indicies[j + 1], indicies[j + 2]);
		printf("%i, %i, %i\n\n", indicies[j + 3], indicies[j + 4], indicies[j + 5]);
		j+=6;
#endif
		
		// right
		indicies[index + 30] = val + 1;
		indicies[index + 31] = val + 5;
		indicies[index + 32] = val + 6;
		indicies[index + 33] = val + 6;
		indicies[index + 34] = val + 2;
		indicies[index + 35] = val + 1;
		
#ifdef PRINT_INDICIES
		printf("%i, %i, %i, \n", indicies[j + 0], indicies[j + 1], indicies[j + 2]);
		printf("%i, %i, %i\n\n", indicies[j + 3], indicies[j + 4], indicies[j + 5]);
		j+=6;
#endif
		
		// We're not the last
		if (i + 1 < total)
		{
			indicies[index + 36] = val + 1;
			indicies[index + 37] = val + 8;
			
#ifdef PRINT_INDICIES
			printf("-- %i, %i --\n\n", indicies[index + 36], indicies[index + 37]);
			j+=2;
#endif
		}
		
		index += INDICIES_PER_CUBE;
		val += VERTS_PER_CUBE;
	}
	
#ifdef PRINT_INDICIES
	printf("END!\n");
#endif
}

void CubeManager::generateVertsFromCubes(ColorVertex* verts)
{
	
	// Unit cube
	static const Point3F pts[VERTS_PER_CUBE] =
	{
		// Front
		Point3F( 0.0f,  0.0f,  1.0f),
		Point3F( 1.0f,  0.0f,  1.0f),
		Point3F( 1.0f,  1.0f,  1.0f),
		Point3F( 0.0f,  1.0f,  1.0f),
		
		// Back
		Point3F( 0.0f,  0.0f,  0.0f),
		Point3F( 1.0f,  0.0f,  0.0f),
		Point3F( 1.0f,  1.0f,  0.0f),
		Point3F( 0.0f,  1.0f,  0.0f)
	};
	
	static const Color4u colors[VERTS_PER_CUBE] =
	{
		Color4u(100, 200, 100, 175),
		Color4u(100, 200, 100, 175),
		Color4u(100, 200, 100, 175),
		Color4u(100, 200, 100, 175),
		Color4u(200, 100, 100, 175),
		Color4u(200, 100, 100, 175),
		Color4u(200, 100, 100, 175),
		Color4u(200, 100, 100, 175),
	};
	
	GLuint total = _size.volume();
	GLuint idx = 0;
	for (GLuint i = 0; i < total; i++)
	{
		for (GLuint j = 0; j < VERTS_PER_CUBE; j++, idx++)
		{
			verts[idx].location.set(_cubes[i].location());
			verts[idx].location.add(pts[j]);
			verts[idx].color.set(colors[j]);
		}
	}
}

