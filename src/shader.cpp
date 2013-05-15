//
//  shader.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "log.h"
#include "shader.h"

GLuint Shader::_currentProgram = 0;

Shader::Shader()
{}

Shader::~Shader()
{
	
}

bool Shader::init(const char *vsh, const char *fsh, VertexFormat f)
{
	_format = f;
	_id = glCreateProgram();
	
	GLuint vert, frag;
	
	if (!compileShader(vsh, GL_VERTEX_SHADER, vert))
		return false;
	
	if (!compileShader(fsh, GL_FRAGMENT_SHADER, frag))
		return false;
	
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
	}
	
	return true;
}