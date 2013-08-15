//
//  shaderManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/23/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "glutil.h"
#include "shaderManager.h"

ShaderFormat ShaderManager::_currentProgramID = NUM_SHADER_TYPES;
ShaderManager ShaderManager::_instance;

ShaderManager::ShaderManager()
{}

ShaderManager::~ShaderManager()
{
	
}

bool ShaderManager::init()
{
	info("Initializing %u shaders.", NUM_SHADER_TYPES);
	
	for (ShaderFormat i = (ShaderFormat)0; i < NUM_SHADER_TYPES; i++)
	{
		if (!_shaders[i].init(ShaderFormats::definitions[i]))
			return false;
	}
	
	return true;
}

void ShaderManager::applyProjectionMVP(const glm::mat4 &mvp, ProjectionStyle style)
{
	for (ShaderFormat i = (ShaderFormat)0; i < NUM_SHADER_TYPES; i++)
	{
		if (ShaderFormats::definitions[i].projection == style)
		{
			setMVP(mvp, i);
		}
	}
}
