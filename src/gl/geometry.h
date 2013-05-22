//
//  geometry.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__geometry__
#define __SpaceJunk__geometry__

#pragma mark Matrix types
typedef float matrix4f[16];
typedef float matrix3f[9];
typedef float matrix2f[4];

struct Point2Di
{
	Point2Di() : x(0), y(0) {};
	Point2Di(GLuint _x, GLuint _y) : y(_y), x(_x) {};
	Point2Di(const Point2Di& p) : y(p.y), x(p.x) {};
	
	GLuint x, y;
};

struct Size2D
{
	Size2D() : width(0), height(0) {};
	Size2D(GLuint _width, GLuint _height) : width(_width), height(_height) {};
 	Size2D(const Size2D& s) : width(s.width), height(s.height) {};
	
	GLuint width;
	GLuint height;
};

struct Rect2Di
{
	Rect2Di() : Size2D(), position() {};
	Rect2Di(GLuint _width, GLuint _height) : Size2D(_width, _height), position() {};
	Rect2Di(GLuint _y, GLuint _x, GLuint _width, GLuint _height) :
		Size2D(_width, _height), position(_y, _x) {};
	Rect2Di(const Size2D& s, const Point2Di& p) : Size2D(s), position(p) {};
	Rect2Di(const Rect2Di& r) : Size2D(r.Size2D), position(r.position) {};
	
	Size2D Size2D;
	Point2Di position;
};

struct Point2Df
{
	Point2Df() : x(0), y(0) {};
	Point2Df(GLfloat _x, GLfloat _y) : y(_y), x(_x) {};
	Point2Df(const Point2Di& p) : y(p.y), x(p.x) {};
	
	union { GLfloat x; GLfloat s; };
	union { GLfloat y; GLfloat t; };
};

struct Point3Df
{
	Point3Df() : y(0.0f), x(0.0f), z(0.0f) {};
	Point3Df(GLfloat _x, GLfloat _y, GLfloat _z) : y(_y), x(_x), z(_z) {};
	Point3Df(GLfloat _x, GLfloat _y) : y(_y), x(_x), z(0.0f) {};
	Point3Df(const Point3Df& p) : y(p.y), x(p.x), z(p.z) {};
	
	GLfloat x, y, z;
};

#endif /* defined(__SpaceJunk__geometry__) */
