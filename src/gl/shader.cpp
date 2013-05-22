//
//  shader.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "glutil.h"

#include "file.h"
#include "shader.h"

GLuint Shader::_currentProgram = 0;

Shader::Shader() : _id(0), _vert(0), _frag(0)
{}

Shader::~Shader()
{
	if (_id) glDeleteProgram(_id);
	if (_vert) glDeleteShader(_vert);
	if (_frag) glDeleteShader(_frag);
}

bool Shader::init(const char* const name,
									const VertexAttribute** attrs,
									GLuint cnt)
{
	File vsh, fsh;
	
	_id = glCreateProgram();
	
	// Load the vertex shader and compile it
	vsh.init(name, "vsh");
	if (!compileShader(vsh.contents(), GL_VERTEX_SHADER, _vert))
		return false;
	
	// Load the frag shader and compile it
	fsh.init(name, "fsh");
	if (!compileShader(fsh.contents(), GL_FRAGMENT_SHADER, _frag))
		return false;
	
	if (!link(_frag, _vert))
		return false;
	
	log("Successfully created shader %s at ID %i", name, _id);
	
	return true;
}

bool Shader::compileShader(const char *src, GLenum type, GLuint &s)
{
	s = glCreateShader(type);
	glShaderSource(s, 1, &src, NULL);
	glCompileShader(s);
	
	GetGLError();
	
	// Error checking
	GLint status;
	glGetShaderiv(s, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		error("failed to compile %s shader",
					type == GL_FRAGMENT_SHADER ? "fragment" : "vertex");
		
		GLint logLen = 0;
		GLsizei length = 0;
		GLchar* log = NULL;
		
		glGetShaderiv(s, GL_INFO_LOG_LENGTH, &logLen);
		
		if (logLen)
		{
			log = new GLchar[logLen];
			glGetShaderInfoLog(s, logLen, &length, log);
			log("Shader Compile Log: \n\n%s", log);
			delete [] log;
		}
		
		return false;
	}
	
	// Attach, since it's good
	glAttachShader(_id, s);
	GetGLError();
	
	return true;
}

bool Shader::link(GLuint frag, GLuint vert)
{
	
	glLinkProgram(_id);
	
	// Dump program compilation log
	GLint logLength = 0;
	glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength)
	{
		char* log = new char[logLength];
		glGetProgramInfoLog(_id, logLength, &logLength, log);
		log("Shader Link Log: \n\n%s", log);
		delete [] log;
	}
	
	GLint status;
	glGetProgramiv(_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		error("Failed to link program %d.", _id);
		return false;
	}
	
	return true;
}

bool Shader::applyVertexFormat(const VertexAttribute **attrs, GLuint count)
{
	for (GLuint i = 0; i < count; i++)
	{
		glBindAttribLocation(_id, i, attrs[i]->name);
		GetGLError();
	}
	
	return true;
}

GLint Shader::getAttrLocation(const char *const attrName) const
{
	return glGetAttribLocation(_id, attrName);
}

GLint Shader::getUniformLocation(const char *const uniName) const
{
	return glGetUniformLocation(_id, uniName);
}
