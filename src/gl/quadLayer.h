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
#include "shaderManager.h"
#include "triangleBuffer.h"

class QuadLayer
{
public:
	
	QuadLayer();
	~QuadLayer();
	
	bool init(GLuint maxQuads, ShaderFormat shaderFormat);
	
	inline void draw() const
	{
		ShaderManager::use(_shaderFormat);
		_buffer.draw();
		GetGLError();
	};
	
private:
	
	GLuint _maxQuads;
	
	ShaderFormat _shaderFormat;
	TriangleBuffer _buffer;
	
};

#endif /* defined(__SpaceJunk__quadLayer__) */
