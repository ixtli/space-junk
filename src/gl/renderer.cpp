//
//  renderer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "glutil.h"

#include "shaderManager.h"

#include "colorRectLayer.h"

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
    delete r;
	delete _layer;
}

bool Renderer::init(GLuint defaultFBO)
{
	// Emit some basic data about the environment
	log("Hardware Renderer: %s", glGetString(GL_RENDERER));
	log("OpenGL Version: %s", glGetString(GL_VERSION));
	log("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	// Save the default VBO
	_defaultFBOName = defaultFBO;
	
	resetGL();
	
	// Initialize Shaders
	if (!ShaderManager::getInstance()->init())
		return false;
	
    // TODO: Remove temp data
    r = new ColorRect();
    r->depthOffset = 0;
    r->rect.bounds.width = 27;
    r->rect.bounds.height = 38;
    r->rect.position.x = 10;
    r->rect.position.y = 32;
    r->color.r = 180;
    r->color.g = 90;
    r->color.b = 5;
    r->color.a = 200;
    
    _layer = new ColorRectLayer();
    _layer->init(0, 1);
    _layer->addRect(r);
    _layer->commit();
    
	return true;
}

void Renderer::resize(const Size2Di& newBounds)
{
	_bounds.width = newBounds.width;
	_bounds.height = newBounds.height;
	
	// Reset the viewport based on the new bounds
	glViewport(0, 0, (GLsizei)_bounds.width, (GLsizei)_bounds.height);
	
	// Load a new ortho matrix for the model view projection
	loadOrtho(0.0f, _bounds.width, _bounds.height, 0.0f, projectionNear,
						projectionFar, _projectionMatrix);
	
	// Update all shaders with the new MVP
	ShaderManager::getInstance()->setMVPMatrix(_projectionMatrix);
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

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	_layer->draw();
	
	GetGLError();
}

