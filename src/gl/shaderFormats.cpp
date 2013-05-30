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
		.attrs = VertexFormats::solidQuadList
	}
};