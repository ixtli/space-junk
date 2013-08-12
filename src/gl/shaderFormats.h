//
//  shaderFormats.h
//  SpaceJunk
//
//  Created by ixtli on 5/24/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef SpaceJunk_shaderFormats_h
#define SpaceJunk_shaderFormats_h

#include "vertexFormats.h"

typedef enum
{
	SOLID_QUAD_SHADER,
	SOLID_CUBE_SHADER,
	NUM_SHADER_TYPES
} ShaderFormat;

struct ShaderMetadata
{
	const char* const name;
	const unsigned attrCount;
	const VertexAttribute* const* attrs;
	const ProjectionStyle projection;
};

class ShaderFormats
{
public:
	static const ShaderMetadata definitions[NUM_SHADER_TYPES];
};

#endif
