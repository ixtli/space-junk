//
//  vertexFormats.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/29/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "vertexFormats.h"

constexpr const VertexAttribute VertexFormats::attributes[NUM_VERTEX_ATTRIBUTES] =
{
	// POSITION_ATTRIB
	{
		.size = 3,	// x, y, z
		.type = GL_FLOAT,
		.normalize = GL_FALSE,
		.name = "v_pos",
		.byteCount = sizeof(Point3F)
	},
	
	// TEXTURED_ATTRIB
	{
		.size = 2,	// s, t
		.type = GL_FLOAT,
		.normalize = GL_FALSE,
		.name = "v_texCoord",
		.byteCount = sizeof(Point2F)
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

constexpr const VertexAttribute* const VertexFormats::solidQuadList[] =
{
	&attributes[POSITION_ATTRIB],
	&attributes[COLORED_ATTRIB]
};
