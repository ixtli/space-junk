//
//  vertexFormats.h
//  SpaceJunk
//
//  Created by ixtli on 5/20/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef SpaceJunk_vertexFormats_h
#define SpaceJunk_vertexFormats_h

#include "geometry.h"
#include "color.h"

typedef struct
{
	Point3F location;
	Point2F texCoord;
} TextureVertex;

class ColorVertex
{
public:
	Point3F location;
	Color4u color;
};

typedef struct
{
	const GLint size;								// how many vars in the attr
	const GLenum type;							// type of vars in the attr
	const GLboolean normalize;			// normilze these data?
	const GLsizei byteCount;				// the size of the vertex attribute (in bytes)
	const char* const name;					// shader variable name
} VertexAttribute;

/* Below are const definitions, add your vertex formats in kind. */

typedef enum
{
	POSITION_ATTRIB,
	TEXTURED_ATTRIB,
	COLORED_ATTRIB,
	NUM_VERTEX_ATTRIBUTES
} VertexAttributes;

class VertexFormats
{
public:
	
	static const VertexAttribute attributes[NUM_VERTEX_ATTRIBUTES];
	static const VertexAttribute* const solidQuadList[];
	
};

#endif
