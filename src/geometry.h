//
//  geometry.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__geometry__
#define __SpaceJunk__geometry__

struct Point2D
{
	Point2D() : top(0), left(0) {};
	Point2D(GLuint _top, GLuint _left) : top(_top), left(_left) {};
	Point2D(const Point2D& p) : top(p.top), left(p.left) {};
	
	GLuint top;
	GLuint left;
};

struct Size2D
{
	Size2D() : width(0), height(0) {};
	Size2D(GLuint _width, GLuint _height) : width(_width), height(_height) {};
 	Size2D(const Size2D& s) : width(s.width), height(s.height) {};
	
	GLuint width;
	GLuint height;
};

struct Rect2D
{
	Rect2D() : Size2D(), position() {};
	Rect2D(GLuint _width, GLuint _height) : Size2D(_width, _height), position() {};
	Rect2D(GLuint _top, GLuint _left, GLuint _width, GLuint _height) :
		Size2D(_width, _height), position(_top, _left) {};
	Rect2D(const Size2D& s, const Point2D& p) : Size2D(s), position(p) {};
	Rect2D(const Rect2D& r) : Size2D(r.Size2D), position(r.position) {};
	
	Size2D Size2D;
	Point2D position;
};

#endif /* defined(__SpaceJunk__geometry__) */
