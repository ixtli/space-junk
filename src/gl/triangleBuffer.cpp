//
//  triangleBuffer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/20/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "glutil.h"

#include "renderer.h"

#include "triangleBuffer.h"

TriangleBuffer::TriangleBuffer() :

_dynamic(GL_TRUE),
_vertexCount(0),
_vaoID(0),
_vertexBufferID(0),
_indexBufferID(0),
_vertexSize(0),
_indexCount(0)

{ }

TriangleBuffer::~TriangleBuffer()
{
	// Don't try to delete VAO id 0
	if (!_vaoID) return;
	
	Renderer::bindVAO(_vaoID);
	
	glDeleteBuffers(1, &_vertexBufferID);
	glDeleteBuffers(1, &_indexBufferID);
	glDeleteVertexArrays(1, &_vaoID);
	
	Renderer::clearBindings();
}

bool TriangleBuffer::init(const TriBufferConfig &config)
{
	if (!config.vertexCount)
	{
		error("No reason to initialize a buffer with a 0 initial size.");
		return false;
	}
	
	if (!config.indexCount)
	{
		error("No reason to initialie a buffer with no indicies.");
		return false;
	}
	
	// Save things useful to us later
	_indexCount = config.indexCount;
	_vertexCount = config.vertexCount;
	_dynamic = config.dynamic;
	
	// Calculate total vertex size from count and vertex attrs
	for (GLuint i = 0; i < config.attrCount; i++)
		_vertexSize += config.attributes[i]->stride;
	
	// Create the VAO
	glGenVertexArrays(1, &_vaoID);
	GetGLError();
	
	// Check for errors here because this is a newer feature of OpenGL
	if (!_vaoID)
	{
		error("Couldn't create vertex array object.");
		return false;
	}
	
	Renderer::bindVAO(_vaoID);
	GetGLError();
	
	// Create the vertex data buffers
	glGenBuffers(1, &_vertexBufferID);
	arrayBufferData(config.verticies);
	
	// Create the element index buffer
	glGenBuffers(1, &_indexBufferID);
	elementBufferData(config.indicies);
	
	// Enable and set vertex attribute arrays
	GLsizei offset = 0;
	for (GLuint i = 0; i < config.attrCount; i++)
	{
		glEnableVertexAttribArray(i);
		
		GetGLError();
		
		glVertexAttribPointer(i,
													config.attributes[i]->size,
													config.attributes[i]->type,
													config.attributes[i]->normalize,
													_vertexSize,
													(const void*)offset);
		
		GetGLError();
		
		offset += config.attributes[i]->stride;
	}
	
	Renderer::clearBindings();
	
	log("Created VAO %i (vert: %i, index: %i)",
			_vaoID, _vertexBufferID, _indexBufferID);
	
	return true;
}

void TriangleBuffer::arrayBufferData(const GLvoid *data)
{
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER,
							 ((GLsizeiptr)_vertexSize * _vertexCount), data,
							 _dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	GetGLError();
}

void TriangleBuffer::elementBufferData(const GLushort *data)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
							 (GLsizei)(sizeof(GLushort) * _indexCount),
							 data, GL_DYNAMIC_DRAW);
	GetGLError();
}

