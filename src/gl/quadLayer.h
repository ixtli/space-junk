//
//  quadLayer.h
//  SpaceJunk
//
//  Created by ixtli on 5/24/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__quadLayer__
#define __SpaceJunk__quadLayer__

#include "glutil.h"

#include "geometry.h"
#include "shaderManager.h"
#include "triangleBuffer.h"

class QuadLayer
{
public:
	
	QuadLayer(bool dynamic = true);
	~QuadLayer();
	
	bool init(GLuint maxQuads, ShaderFormat shader, const GLvoid* verts);
	
	// Inline render functions
	inline void draw() const
	{
		ShaderManager::use(_shaderFormat);
		_buffer.draw();
		GetGLError();
	};
	
private:
	
	void generateElementIndicies(GLushort* indicies);
	
	bool _dynamic;
	GLuint _maxQuads;
	
	ShaderFormat _shaderFormat;
	TriangleBuffer _buffer;
	
};

#endif /* defined(__SpaceJunk__quadLayer__) */
