//
//  textureManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/30/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "textureManager.h"

TextureManager TextureManager::_instance;

TextureManager::TextureManager() :

_textureUnits(0),
_unitsUsed(0),
_evictions(0),
_textureUnitQueue()

{}

TextureManager::~TextureManager()
{
	
}

bool TextureManager::init()
{
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_textureUnits);
	info("Texture units available: %i", _textureUnits);
	
	return true;
}
