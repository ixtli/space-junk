//
//  renderer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "log.h"
#include "renderer.h"

Renderer Renderer::_instance;

Renderer::Renderer() : bounds(), defaultFBOName(0)
{ }

Renderer::~Renderer()
{
	
}

bool Renderer::initialize(GLuint defaultFBO)
{
	log("%s %s\n", glGetString(GL_RENDERER), glGetString(GL_VERSION));
	log("GLSL v%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	// Save the default VBO
	defaultFBOName = defaultFBO;
	
	resetGL();
	
	return true;
}

void Renderer::resize(const Size2D& newBounds)
{
	bounds.width = newBounds.width;
	bounds.height = newBounds.height;
	
	glViewport(0, 0, (GLsizei)bounds.width, (GLsizei)bounds.height);
}

void Renderer::resetGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

