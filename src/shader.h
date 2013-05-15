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
	
	static const GLuint VERT_POS_LOC = 0;       // position is always first
	static const GLuint VERT_TEX_LOC = 1;
	static const GLuint VERT_COL_LOC = 1;
	
	static const GLuint POINT_PART_RAD_LOC = 1;
	static const GLuint POINT_PART_COL_LOC = 2;
	static const GLuint POINT_PART_TEX_LOC = 3;
	
	static const GLuint TEX_PART_COL_LOC = 1;
	static const GLuint TEX_PART_TEX_LOC = 2;
	
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
	bool link(GLuint frag, GLuint vert);
	
	void applyVertexFormat();
	
	static GLuint _currentProgram;
	
	VertexFormat _format;
	GLuint _id, _vert, _frag;
	
};

#endif /* defined(__SpaceJunk__shader__) */
