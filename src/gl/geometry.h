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

struct Point3Di
{
	Point3Di() : x(0), y(0), z(0) {};
	
	Point3Di(GLuint _x, GLuint _y) : y(_y), x(_x), z(0) {};
	Point3Di(const Point2Di& p) : y(p.y), x(p.x) {};
	
	Point3Di(GLuint _x, GLuint _y, GLuint _z) : y(_y), x(_x), z(_z) {};
	Point3Di(const Point3Di& p) : y(p.y), x(p.x), z(p.z) {};
	
	GLuint x, y, z;
};

struct Size2Di
{
	Size2Di() : width(0), height(0) {};
	Size2Di(GLuint _width, GLuint _height) : width(_width), height(_height) {};
	Size2Di(const Size2Di& s) : width(s.width), height(s.height) {};
	
	GLuint width;
	GLuint height;
};

struct Rect2Di
{
	Rect2Di() : bounds(), position() {};
	Rect2Di(GLuint _width, GLuint _height) : bounds(_width, _height), position() {};
	Rect2Di(GLuint _y, GLuint _x, GLuint _width, GLuint _height) :
		bounds(_width, _height), position(_y, _x) {};
	Rect2Di(const Size2Di& s, const Point2Di& p) : bounds(s), position(p) {};
	Rect2Di(const Rect2Di& r) : bounds(r.bounds), position(r.position) {};
	Rect2Di(const Size2Di& s) : bounds(s) {};
	
	Size2Di bounds;
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
