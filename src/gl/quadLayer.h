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
	bool resizeLayer(GLuint newMaxQuads);
	
	// Inline render functions
	inline void draw() const
	{
		ShaderManager::use(_shaderFormat);
		_buffer.draw();
		GetGLError();
	};
	
	// Inline getters and setters
	void usedQuads(GLuint used);
	inline bool update(const GLvoid* verts) {return _buffer.updateVerts(verts);};
	inline GLuint usedQuads() const { return _usedQuads; };
	
private:
	
	void generateElementIndicies(GLushort* indicies);
	
	bool _dynamic;
	GLuint _usedQuads;
	GLuint _maxQuads;
	
	ShaderFormat _shaderFormat;
	TriangleBuffer _buffer;
	
};

#endif /* defined(__SpaceJunk__quadLayer__) */
