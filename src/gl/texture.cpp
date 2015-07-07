//
//  texture.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/23/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "textureManager.h"

#include "texture.h"

Texture::Texture() :

_id(0),
_textureUnit(-1)

{ }


Texture::~Texture()
{
	if (_id > 0)
	{
		glDeleteTextures(1, &_id);
		_id = 0;
	}
}

bool Texture::init(GLsizei width, GLsizei height, const void* data)
{
	glGenTextures(1, &_id);
	
	glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	if (!TextureManager::bind(this))
	{
		error("failed to bind texture on init.");
	}
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
							 GL_UNSIGNED_BYTE, data);
	
	GetGLError();
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	return true;
}
