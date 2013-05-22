//
//  renderer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "shader.h"
#include "triangleBuffer.h"

#include "renderer.h"

Renderer Renderer::_instance;
GLuint Renderer::_currentVAO = 0;

Renderer::Renderer() : _bounds(), _defaultFBOName(0)
{ }

Renderer::~Renderer()
{
	delete _buffer;
	delete _solidQuad;
}

bool Renderer::init(GLuint defaultFBO)
{
	// Emit some basic data about the environment
	log("Hardware Renderer: %s", glGetString(GL_RENDERER));
	log("OpenGL Version: %s", glGetString(GL_VERSION));
	log("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
	
	GLint max_vertex_attrs = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attrs);
	log("GL_MAX_VERTEX_ATTRIBS: %i", max_vertex_attrs);
	
	// Save the default VBO
	_defaultFBOName = defaultFBO;
	
	resetGL();
	
	// Construct some temp data
	
	static GLushort indicies[] = {0, 1, 2, 3};
	
	GLfloat size = 100.0f;
	
	static ColorVertex verts[] = {
		{
			// Bottom left
			.location = Point3Df(0, size, 0),
			.color = Color4u(100, 0, 0, 255)
		},
		{
			// Bottom right
			.location = Point3Df(size, size, 0),
			.color = Color4u(100, 0, 0, 255)
		},
		{
			// Top left
			.location = Point3Df(0, 0, 0),
			.color = Color4u(100, 0, 0, 255)
		},
		{
			// Top right
			.location = Point3Df(size, 0, 0),
			.color = Color4u(100, 0, 0, 255)
		},
	};
	
	const VertexAttribute* attrs[] = {
		&vertexAttributeDefinitions[POSITION_ATTRIB],
		&vertexAttributeDefinitions[COLORED_ATTRIB]
	};
	
	const TriangleBuffer::TriBufferConfig conf = {
		.dynamic = false,
		.vertexCount = 4,
		.indexCount = 4,
		.attrCount = 2,
		.indicies = indicies,
		.verticies = verts,
		.attributes = attrs
	};
	
	// Construct shaders
	_solidQuad = new Shader();
	if (!_solidQuad->init("solidQuad", attrs, conf.attrCount)) return false;
	
	// Construct buffer
	_buffer = new TriangleBuffer();
	if (!_buffer->init(conf)) return false;
	
	return true;
}

void Renderer::resize(const Size2D& newBounds)
{
	_bounds.width = newBounds.width;
	_bounds.height = newBounds.height;
	
	glViewport(0, 0, (GLsizei)_bounds.width, (GLsizei)_bounds.height);
	
	// Load a new ortho matrix
	loadOrtho(0.0f, _bounds.width, _bounds.height, 0.0f, -1.0f, 1.0f, _projectionMatrix);
	
	_solidQuad->use();
	GLint loc = _solidQuad->getUniformLocation("modelViewProjectionMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, _projectionMatrix);
	
	GetGLError();
}

void Renderer::resetGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DITHER);
	glDisable(GL_STENCIL_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	_solidQuad->use();
	bindVAO(_buffer->vao());
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, 0);
	
	GetGLError();
}

