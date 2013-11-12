//
//  renderer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "glutil.h"
#include "geometry.h"
#include "shaderManager.h"
#include "uiManager.h"
#include "cubeManager.h"

#include "renderer.h"

// Static member initialization
Renderer Renderer::_instance;
GLuint Renderer::_currentVAO = 0;
const GLfloat Renderer::projectionNear = -1.0f;
const GLfloat Renderer::projectionFar = 1.0f;

Renderer::Renderer() : _bounds(), _defaultFBOName(0)
{ }

Renderer::~Renderer()
{
	
}

bool Renderer::init(GLuint defaultFBO)
{
	// Emit some basic data about the environment
	info("Hardware Renderer: %s", glGetString(GL_RENDERER));
	info("OpenGL Version: %s", glGetString(GL_VERSION));
	info("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	// Save the default VBO
	_defaultFBOName = defaultFBO;
	
	resetGL();
	
	// Initialize Shaders
	if (!ShaderManager::getInstance()->init())
		return false;
	
	return true;
}

void Renderer::resize(const Size2I& newBounds)
{
	// Save new bounds
	_bounds.set(newBounds);
	
	// Reset the viewport based on the new bounds
	glViewport(0, 0, (GLsizei)_bounds.width, (GLsizei)_bounds.height);
		
	// Load a new ortho matrix
	glm::mat4 ortho = glm::ortho(0.0f,
															 (GLfloat)_bounds.width,
															 (GLfloat)_bounds.height,
															 0.0f,
															 projectionNear,
															 projectionFar);
	
	// Apply that matrix to all ortho shaders
	ShaderManager::getInstance()->applyProjectionMVP(ortho, ORTHOGRAPHIC_PROJECTION);
	
	// Update managers with the resize event
	UIManager::getInstance()->viewDidResize(_bounds);
	CubeManager::getInstance()->viewDidResize(_bounds);
}

void Renderer::resetGL()
{
	// Enable things we want
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	
	// Disable things we don't need
	glDisable(GL_CULL_FACE);
	glDisable(GL_DITHER);
	glDisable(GL_STENCIL_TEST);
	
	// Set global state
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::render(sjtime_t currentTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	CubeManager::draw();
	UIManager::draw();
	
	GetGLError();
}

