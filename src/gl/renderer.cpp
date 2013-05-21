//
//  renderer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "triangleBuffer.h"

#include "renderer.h"

Renderer Renderer::_instance;

Renderer::Renderer() : bounds(), defaultFBOName(0)
{ }

Renderer::~Renderer()
{
	
}

bool Renderer::init(GLuint defaultFBO)
{
	// Emit some basic data about the environment
	log("Hardware Renderer: %s", glGetString(GL_RENDERER));
	log("OpenGL Version: %s", glGetString(GL_VERSION));
	log("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	// Warn if verts aren't going to be well-packed
//	if (sizeof(VertexBuffer::TextureVertex) % 4)
//	{
//		warn("TextureVertex wont align on 4-byte boundries!");
//	}
	
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

