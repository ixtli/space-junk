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

struct Color4u
{
	Color4u() : r(0), g(0), b(0), a(255) {};
	Color4u(const Color4u& c) : r(c.r), g(c.g), b(c.b), a(c.a) {};
	
	Color4u(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a) :
		r(_r), g(_g), b(_b), a(_a) {};
	
	GLubyte r, g, b, a;
};

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
