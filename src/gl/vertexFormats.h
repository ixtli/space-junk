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

const static VertexAttribute vertexAttributeDefinitions[NUM_VERTEX_ATTRIBUTES] =
{
	// POSITION_ATTRIB
	{
		.size = 3,	// x, y, z
		.type = GL_FLOAT,
		.normalize = GL_FALSE,
		.name = "v_pos",
		.byteCount = sizeof(Point3Df)
	},
	
	// TEXTURED_ATTRIB
	{
		.size = 2,	// s, t
		.type = GL_FLOAT,
		.normalize = GL_FALSE,
		.name = "v_texCoord",
		.byteCount = sizeof(Point2Df)
	},
	
	// COLORED_ATTRIB
	{
		.size = 4,	// r, g, b, a (no padding required)
		.type = GL_UNSIGNED_BYTE,
		.normalize = GL_TRUE,
		.name = "v_color",
		.byteCount = sizeof(Color4u)
	}
};

namespace VertFormat {
	
  const VertexAttribute* const solidQuadList[] =
	{
		&vertexAttributeDefinitions[POSITION_ATTRIB],
		&vertexAttributeDefinitions[COLORED_ATTRIB]
	};
	
}

#endif
