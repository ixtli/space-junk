//
//  color.h
//  SpaceJunk
//
//  Created by Ixtli on 6/2/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__color__
#define __SpaceJunk__color__

struct Color4u
{
	Color4u() : r(0), g(0), b(0), a(255) {};
	Color4u(const Color4u& c) : r(c.r), g(c.g), b(c.b), a(c.a) {};
	
	Color4u(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a) :
	r(_r), g(_g), b(_b), a(_a) {};
	
	GLubyte r, g, b, a;
};

#endif /* defined(__SpaceJunk__color__) */
