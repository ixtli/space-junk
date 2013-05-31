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
	bool updateVerts(const GLvoid* verticies);
	bool updateIndicies(const GLushort* indicies);
	
	// Size manipulation functions
	// Data expected to be difference between old count and new, and is appended
	// to the end of the buffer after it is copied
	bool growVertsReplace(GLuint newVertCount, const GLvoid* verticies);
	bool growIndiciesReplace(GLuint newIndexCount, const GLushort* indicies);
	
	// Data expected to be the size of the new count, the old buffer is REMOVED
	// and the new data is used instead
	bool growVertsExtend(GLuint newVertCount, const GLvoid* verticies);
	bool growIndiciesExtend(GLuint newIndexCount, const GLushort* indicies);
	
	// Data is optional: if provided it replaces the old data, otherwise the old
	// data is truncated and copied to the new buffer location
	bool shrinkVerts(GLuint newVertCount, const GLvoid* verticies);
	bool shrinkIndicies(GLuint newIndexCount, const GLushort* indicies);
  
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
