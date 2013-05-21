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
	
	bool init(bool dynamic, GLuint attrCount, const VertexAttribute** attrs);
	
private:
	
	GLuint _attrCount;
	const VertexAttribute** _vertexAttrs;
	GLuint _vertexCount;
	bool _dynamic;
	
};

#endif /* defined(__SpaceJunk__triangleBuffer__) */
