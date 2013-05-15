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

Shader::Shader() : _id(0), _vert(0), _frag(0)
{}

Shader::~Shader()
{
	if (_id) glDeleteProgram(_id);
	if (_vert) glDeleteShader(_vert);
	if (_frag) glDeleteShader(_frag);
}

bool Shader::init(const char *vsh, const char *fsh, VertexFormat f)
{
	_format = f;
	_id = glCreateProgram();
	
	if (!compileShader(vsh, GL_VERTEX_SHADER, _vert))
		return false;
	
	if (!compileShader(fsh, GL_FRAGMENT_SHADER, _frag))
		return false;
	
	if (!link(_frag, _vert))
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
	
	return true;
}

bool Shader::link(GLuint frag, GLuint vert)
{
	
	glAttachShader(_id, frag);
	glAttachShader(_id, vert);
	
	applyVertexFormat();
	
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

void Shader::applyVertexFormat()
{
	glBindAttribLocation(_id, VERT_POS_LOC, "v_pos");
	
	switch (_format)
	{
		case POS3F_COL4B:
			glBindAttribLocation(_id, VERT_TEX_LOC, "v_color");
			break;
			
		case POS3F_TEX2F:
			glBindAttribLocation(_id, VERT_COL_LOC, "v_texCoord");
			break;
			
		case PARTICLE:
			glBindAttribLocation(_id, POINT_PART_RAD_LOC, "v_radius");
			glBindAttribLocation(_id, POINT_PART_COL_LOC, "v_color");
			break;
			
		case TEXTURED_PARTICLE:
			glBindAttribLocation(_id, TEX_PART_COL_LOC, "v_color");
			glBindAttribLocation(_id, TEX_PART_TEX_LOC, "v_tex");
			break;
			
		default:
			warn("Unknown vertex format %u", _format);
			break;
	}
}

GLint Shader::getAttrLocation(const char *const attrName) const
{
	return glGetAttribLocation(_id, attrName);
}

GLint Shader::getUniformLocation(const char *const uniName) const
{
	return glGetUniformLocation(_id, uniName);
}
