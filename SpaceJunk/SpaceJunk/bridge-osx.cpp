//
//  bridge-osx.cpp
//  SpaceJunk
//
//  Created by ixtli on 10/10/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "bridge-osx.h"

#include "renderer.h"

void initializeRenderer()
{
	// Init our renderer. Use zero for the default FBO
	// N.B.: Not appropriate for iOS
	Renderer::getInstance()->init(0);
}

void resizeView(unsigned int w, unsigned h)
{
	Renderer::getInstance()->resize(Size2I(w, h));
}

void render()
{
	Renderer::getInstance()->render();
}