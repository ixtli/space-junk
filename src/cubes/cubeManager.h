//
//  cubescene.h
//  SpaceJunk
//
//  Created by ixtli on 8/11/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__cubeScene__
#define __SpaceJunk__cubeScene__

#include "shaderFormats.h"
#include "triangleBuffer.h"
#include "cube.h"

class CubeManager
{
public:
	
	inline static CubeManager* instance() { return &_instance; };
	
	bool init(const Size3U &size, ShaderFormat format);
	static void draw();
	
private:
	
	// Static or hidden
	CubeManager();
	~CubeManager();
	static CubeManager _instance;
	
	// Convenience const values
	static const GLuint SIDE_COUNT = 6;
	static const GLuint VERTS_PER_CUBE = 8;
	static const GLuint INDICIES_PER_CUBE = 36;
	
	// Helpers
	void generateElementIndicies(GLushort* indicies);
	void generateVertsFromCubes(ColorVertex* verts);
	
	// Member fields
	ShaderFormat _shaderFormat;
	Size3U _size;
	TriangleBuffer _buffer;
	Cube* _cubes;
	
	ColorVertex* _verts;
	
};

#endif /* defined(__SpaceJunk__cubescene__) */
