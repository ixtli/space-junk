//
//  cube.h
//  SpaceJunk
//
//  Created by ixtli on 8/11/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__cube__
#define __SpaceJunk__cube__

#include "geometry.h"

class Cube
{
public:
	
	Cube();
	~Cube();
	
	bool init();
	
	// Getters
	inline const Point3F* location() const { return &_origin; };
	inline const GLfloat x() const { return _origin.x; };
	inline const GLfloat y() const { return _origin.y; };
	inline const GLfloat z() const { return _origin.z; };
	
	// Setters
	inline void x(GLfloat v) { _origin.x = v; };
	inline void y(GLfloat v) { _origin.y = v; };
	inline void z(GLfloat v) { _origin.z = v; };
	
private:
	
	Point3F _origin;
	
};

#endif /* defined(__SpaceJunk__cube__) */
