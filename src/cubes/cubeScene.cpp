//
//  cubescene.cpp
//  SpaceJunk
//
//  Created by ixtli on 8/11/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "cubeScene.h"

CubeScene CubeScene::_instance;

CubeScene::CubeScene() :

_size(),
_buffer(),
_cubes(NULL)

{}

CubeScene::~CubeScene()
{
	
}

bool CubeScene::init(const Point3i &size)
{
	_size.x = size.x;
	_size.y = size.y;
	_size.z = size.z;
	
	size_t total = _size.x * size.y * size.z;
	
	_cubes = new Cube[total];
	
	if (!_cubes)
	{
		error("Couldn't allocate memeory for cubes.");
		return false;
	}
	
	for (GLuint i = 0; i < total; i++)
	{
		if (!_cubes[i].init())
		{
			error("Error initializing cube %u.", i);
			return false;
		}
	}
	
	_buffer.init(_cubes, total);
	
	return true;
}


