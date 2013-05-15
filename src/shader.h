//
//  shader.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__shader__
#define __SpaceJunk__shader__

#include "glutil.h"

class Shader
{
public:
	
	Shader();
	~Shader();
	
	bool init(const char* vsh, const char* fsh, VertexFormat f);
	
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
	
	static GLuint _currentProgram;
	
	VertexFormat _format;
	GLuint _id;
	
};

#endif /* defined(__SpaceJunk__shader__) */
