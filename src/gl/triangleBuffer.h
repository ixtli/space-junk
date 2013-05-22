//
//  triangleBuffer.h
//  SpaceJunk
//
//  Created by ixtli on 5/20/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__triangleBuffer__
#define __SpaceJunk__triangleBuffer__

#include "vertexFormats.h"

class TriangleBuffer
{
public:
	
	TriangleBuffer();
	~TriangleBuffer();
	
	typedef struct
	{
		bool dynamic;
		
		GLuint vertexCount;
		const GLvoid* verticies;
		GLuint indexCount;
		const GLushort* indicies;
		unsigned attrCount;
		const VertexAttribute** attributes;
		
	} TriBufferConfig;
	
	bool init(const TriBufferConfig &config);
	
	inline GLuint vao() const
	{
		return _vaoID;
	}
	
private:
	
	// Helper functions that you must clean up after
	void arrayBufferData(const GLvoid* data);
	void elementBufferData(const GLushort* data);
	
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
