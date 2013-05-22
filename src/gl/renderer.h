//
//  renderer.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__renderer__
#define __SpaceJunk__renderer__

#include "geometry.h"

class Shader;
class TriangleBuffer;

class Renderer
{
public:
	
	static const GLfloat projectionNear;
	static const GLfloat projectionFar;
	
	inline static Renderer* getInstance() { return &_instance; };
	
	bool init(GLuint defaultFBO);
	void resize(const Size2D& newBounds);
	void render();
	
#pragma mark -
#pragma mark OpenGL Context state manipulation functions
	
	static inline void bindVAO(GLuint vao)
	{
		if (vao == _currentVAO) return;
		
		glBindVertexArray(vao);
		_currentVAO = vao;
	}
	
	static inline void clearBindings()
	{
		bindVAO(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
private:
	
	Renderer();
	~Renderer();
	
	Size2D _bounds;
	matrix4f _projectionMatrix;
	GLuint _defaultFBOName;
	
	TriangleBuffer* _buffer;
	Shader* _solidQuad;
	
	void resetGL();
	
	static Renderer _instance;
	
	// Currently bound GL handles, to avoid too many calls to the GFX card
	static GLuint _currentVAO;
	
};

#endif /* defined(__SpaceJunk__renderer__) */
