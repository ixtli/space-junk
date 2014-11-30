//
//  texture.h
//  SpaceJunk
//
//  Created by ixtli on 11/23/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__texture__
#define __SpaceJunk__texture__

#include "glutil.h"

class Texture
{
public:
	
	Texture();
	~Texture();
	
	bool init(GLsizei width, GLsizei height, const void* data);

	inline void bind(GLint location)
	{
		glActiveTexture(GL_TEXTURE0 + location);
		glBindTexture(GL_TEXTURE_2D, _id);
		_textureUnit = location;
	};
	
	// Get the texture unit that this _id is bound to
	inline GLint textureUnit() const { return _textureUnit; };
	
	// Signify that this texture is not bound to any texture unit
	// N.B.: This may not be true, but is used in management of texture
	// image units by the Texture Manager
	inline void clear() { _textureUnit = -1; };
	
private:
	
	GLuint _id;
	GLint _textureUnit;
	
};

#endif /* defined(__SpaceJunk__texture__) */
