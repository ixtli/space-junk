//
//  shaderFormats.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/29/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "shaderFormats.h"

const ShaderMetadata ShaderFormats::definitions[NUM_SHADER_TYPES] =
{
	{
		.name = "solidQuad",
		.attrCount = 2,
		.attrs = VertexFormats::solidQuadList,
		.projection = ORTHOGRAPHIC_PROJECTION
	},
	{
		.name = "solidCube",
		.attrCount = 2,
		.attrs = VertexFormats::solidQuadList,
		.projection = ISOMETRIC_PROJECTION
	},
	{
		.name = "texturedQuad",
		.attrCount = 2,
		.attrs = VertexFormats::texturedQuadList,
		.projection = ORTHOGRAPHIC_PROJECTION
	}
};
