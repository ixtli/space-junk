//
//  cubescene.h
//  SpaceJunk
//
//  Created by ixtli on 8/11/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__cubeScene__
#define __SpaceJunk__cubeScene__

#include "IComponent.h"

#include "glutil.h"
#include "camera.h"
#include "shaderManager.h"
#include "triangleBuffer.h"
#include "cube.h"

class CubeManager : public IComponent
{
public:
	
	inline static CubeManager* getInstance() { return &_instance; };
	
	virtual bool init();
	virtual void update(uint32_t dt);
	void viewDidResize(const Size2I &bounds);
	
	static void draw();
	
private:
	
	// Static or hidden
	CubeManager();
	virtual ~CubeManager();
	
	// Convenience const values
	static const GLuint SIDE_COUNT = 6;
	static const GLuint VERTS_PER_CUBE = 8;
	static const GLuint INDICIES_PER_CUBE = 38;
	
	// Helpers
	void generateElementIndicies(GLushort* indicies);
	void generateVertsFromCubes(ColorVertex* verts);
	
	// Member fields
	ShaderFormat _shaderFormat;
	Size3U _size;
	TriangleBuffer _buffer;
	Cube* _cubes;
	
	GLushort* _indicies;
	ColorVertex* _verts;
	Camera _camera;
	
	static CubeManager _instance;
	
};

#endif /* defined(__SpaceJunk__cubescene__) */
