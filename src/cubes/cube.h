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
	inline const Point3F& location() { return _location; };
	inline const Size3F& size() { return _size; };
	inline const GLfloat x() const { return _location.x; };
	inline const GLfloat y() const { return _location.y; };
	inline const GLfloat z() const { return _location.z; };
	inline const GLfloat width() const { return _size.width; };
	inline const GLfloat height() const { return _size.height; };
	
	// Setters
	inline void x(GLfloat v) { _location.x = v; };
	inline void y(GLfloat v) { _location.y = v; };
	inline void z(GLfloat v) { _location.z = v; };
	inline void width(GLfloat v) { _size.width = v; };
	inline void height(GLfloat v) { _size.height = v; };
	
private:
	
	Point3F _location;
	Size3F _size;
	
};

#endif /* defined(__SpaceJunk__cube__) */
