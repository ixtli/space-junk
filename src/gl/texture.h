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

	inline void bind() const { glBindTexture(GL_TEXTURE_2D, _id); };
	
private:
	
	unsigned _id;
	
};

#endif /* defined(__SpaceJunk__texture__) */
