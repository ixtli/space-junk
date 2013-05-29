//
//  triangleBuffer.h
//  SpaceJunk
//
//  Created by ixtli on 5/20/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__triangleBuffer__
#define __SpaceJunk__triangleBuffer__

#include "renderer.h"

#include "vertexFormats.h"

class TriangleBuffer
{
public:
	
	typedef struct
	{
		bool dynamic;
		
		GLuint vertexCount;
		const GLvoid* verticies;
		GLuint indexCount;
		const GLushort* indicies;
		unsigned attrCount;
		const VertexAttribute* const* attributes;
		
	} TriBufferConfig;
	
	TriangleBuffer();
	~TriangleBuffer();
	
	bool init(const TriBufferConfig &config);
	bool update(const GLvoid* verticies);
    
	// Getters
	inline GLuint vao() const { return _vaoID; }
	
	// Setters
	inline void count(GLuint c) { _drawCount = (GLsizei)c; };
	inline void start(GLuint s) { _start = (GLvoid*)(s * sizeof(GLushort)); };
	
	// Inline render functions
	inline void draw() const
	{
		Renderer::bindVAO(_vaoID);
		glDrawElements(GL_TRIANGLE_STRIP, _drawCount, GL_UNSIGNED_SHORT, _start);
	}
    
private:
	
	// Helper functions that you must clean up after
	void arrayBufferData(const GLvoid* data);
	void elementBufferData(const GLushort* data);
	
	// The position in the buffer to start drawing from
	GLvoid* _start;
	
	// The amount of indicies from the above to draw
	GLsizei _drawCount;
	
	GLsizei _vertexSize;
	GLuint _indexCount;
	GLuint _vertexCount;
	bool _dynamic;
	
	// GL Handles
	GLuint _vaoID;
	GLuint _vertexBufferID;
	GLuint _indexBufferID;
	
};

#endif /* defined(__SpaceJunk__triangleBuffer__) */
