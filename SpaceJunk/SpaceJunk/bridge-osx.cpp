//
//  bridge-osx.cpp
//  SpaceJunk
//
//  Created by ixtli on 10/10/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include <sys/time.h>

#include "log.h"
#include "engine.h"
#include "renderer.h"

#include "bridge-osx.h"


void resizeView(unsigned int w, unsigned h)
{
	Renderer::getInstance()->resize(Size2I(w, h));
}

void render()
{
	Renderer::getInstance()->render();
}

void updateGameEvent(void* ctx)
{
	static timeval now;
	gettimeofday(&now, NULL);
	Engine::getInstance()->update(now.tv_usec);
}
