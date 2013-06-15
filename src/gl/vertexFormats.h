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
	Point3Df location;
	Point2Df texCoord;
} TextureVertex;

typedef struct
{
	Point3Df location;
	Color4u color;
} ColorVertex;

typedef struct
{
	GLint size;								// how many vars in the attr
	GLenum type;							// type of vars in the attr
	GLboolean normalize;			// normilze these data?
	GLsizei byteCount;				// the size of the vertex attribute (in bytes)
	const char* const name;		// shader variable name
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
