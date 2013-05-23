//
//  shader.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__shader__
#define __SpaceJunk__shader__

#include "vertexFormats.h"

class Shader
{
public:
	
	typedef struct
	{
		const char* const name;
		const unsigned attrCount;
		const VertexAttribute* const* attrs;
	} ShaderMetadata;
	
	Shader();
	~Shader();
	
	bool init(const ShaderMetadata& metadata);
	
	GLint getAttrLocation(const char* const attrName) const;
	GLint getUniformLocation(const char* const uniName) const;
	
	// This is called in the render function
	inline void use() const
	{
		if (_currentProgram != _id)
		{
			glUseProgram(_id);
			_currentProgram = _id;
		}
	}
	
private:
	
	bool compileShader(const char* src, GLenum type, GLuint &s);
	bool link(GLuint frag, GLuint vert);
	bool applyVertexFormat(const ShaderMetadata& metadata);
						
	static GLuint _currentProgram;

	GLuint _id, _vert, _frag;
};

#endif /* defined(__SpaceJunk__shader__) */
