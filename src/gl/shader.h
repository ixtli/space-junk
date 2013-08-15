//
//  shader.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__shader__
#define __SpaceJunk__shader__

#include "shaderFormats.h"

class Shader
{
public:
	
	Shader();
	~Shader();
	
	bool init(const ShaderMetadata& metadata);
	
	GLint getAttrLocation(const char* const attrName) const;
	GLint getUniformLocation(const char* const uniName) const;
	
	// Getters for rendering
	inline GLuint id() const { return _id; };
	inline GLint mvpLoc() const { return _mvpLocation; };
	
private:
	
	static const char* MVP_NAME;
	
	bool compileShader(const char* src, GLenum type, GLuint &s);
	bool link(GLuint frag, GLuint vert);
	bool applyVertexFormat(const ShaderMetadata& metadata);
	
	static GLuint _currentProgram;
	
	GLuint _id, _vert, _frag;
	
	GLint _mvpLocation;
};

#endif /* defined(__SpaceJunk__shader__) */
