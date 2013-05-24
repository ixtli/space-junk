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
	NUM_SHADER_TYPES
} ShaderFormat;

struct ShaderMetadata
{
	const char* const name;
	const unsigned attrCount;
	const VertexAttribute* const* attrs;
};

namespace ShaderFormats {
	
  const ShaderMetadata definitions[NUM_SHADER_TYPES] =
	{
		{
			.name = "solidQuad",
			.attrCount = 2,
			.attrs = VertexFormats::solidQuadList
		}
	};
	
}

#endif
