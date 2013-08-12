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
	log("Initializing %u shaders.", NUM_SHADER_TYPES);
	
	for (ShaderFormat i = (ShaderFormat)0; i < NUM_SHADER_TYPES; i++)
	{
		if (!_shaders[i].init(ShaderFormats::definitions[i]))
			return false;
	}
	
	return true;
}

void ShaderManager::setMVPMatrix(const matrix4f mvp[NUM_PROJECTION_STYLES])
{
	GLint loc = 0;
	
	for (ShaderFormat i = (ShaderFormat)0; i < NUM_SHADER_TYPES; i++)
	{
		use(i);
		loc = _shaders[i].getUniformLocation("modelViewProjectionMatrix");
		
		glUniformMatrix4fv(loc, 1, GL_FALSE,
											 mvp[ShaderFormats::definitions[i].projection]);
	}
	
	GetGLError();
}