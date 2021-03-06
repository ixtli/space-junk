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
#pragma mark -

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#include "glm.hpp"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"
#pragma clang diagnostic pop

typedef enum
{
	ORTHOGRAPHIC_PROJECTION,
	ISOMETRIC_PROJECTION,
	NUM_PROJECTION_STYLES
} ProjectionStyle;

template <class T>
class Point2
{
public:
	Point2() {};
	Point2(const T& _x, const T& _y) : x(_x), y(_y) {};
	Point2(const Point2<T> &p) : x(p.x), y(p.y) {};
	
	inline void set(const Point2<T> &p)
	{
		x = p.x;
		y = p.y;
	};
	
	inline void add(const Point2<T> &p)
	{
		x += p.x;
		y += p.y;
	};
	
	T x, y;
};

typedef Point2<float> Point2F;
typedef Point2<int> Point2I;
typedef Point2<unsigned int> Point2U;
typedef Point2<size_t> Point2L;

template <class T>
class Point3
{
public:
	Point3() {};
	Point3(const T &_x, const T &_y, const T &_z) : x(_x), y(_y), z(_z) {};
	Point3(const Point3<T> &p) : x(p.x), y(p.y), z(p.z) {};
	
	inline void set(const Point3<T> &p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	};
	
	inline void add(const Point3<T> &p)
	{
		x += p.x;
		y += p.y;
		z += p.z;
	};
	
	T x, y, z;
};

typedef Point3<float> Point3F;
typedef Point3<int> Point3I;
typedef Point3<unsigned int> Point3U;
typedef Point3<size_t> Point3L;

template <class T>
class Size2
{
public:
	Size2() {};
	Size2(const T& w, const T& h) : width(w), height(h) {};
	Size2(const Size2<T> &p) : width(p.width), height(p.height) {};
	
	inline void set(const Size2<T> &s)
	{
		width = s.width;
		height = s.height;
	};
	
	T width, height;
};

typedef Size2<float> Size2F;
typedef Size2<int> Size2I;
typedef Size2<unsigned int> Size2U;
typedef Size2<size_t> Size2L;

template <class T>
class Size3
{
public:
	Size3() {};
	Size3(const T& w, const T& h, const T& d) : width(w), height(h), depth(d) {};
	Size3(const Size3<T> &p) : width(p.width), height(p.height), depth(p.depth) {};
	Size3(const Size2<T> &p) : width(p.width), height(p.height), depth() {};
	
	inline void set(const Size3<T> &s)
	{
		width = s.width;
		height = s.height;
		depth = s.depth;
	};
	
	inline T volume() const
	{
		return width * height * depth;
	};
	
	T width, height, depth;
};

typedef Size3<float> Size3F;
typedef Size3<int> Size3I;
typedef Size3<unsigned int> Size3U;
typedef Size3<size_t> Size3L;

template <class T>
class Rectangle
{
public:
	Rectangle() {};
	Rectangle(T width, T height) : bounds(width, height), position() {};
	Rectangle(T x, T y, T width, T height) : bounds(width, height), position(x, y) {};
	Rectangle(const Size2<T> &s, const Point2<T> &p) : bounds(s), position(p) {};
	Rectangle(const Size2<T> &s) : bounds(s), position() {};
	Rectangle(const Point2<T> &p) : bounds(), position(p) {};
	
	Size2<T> bounds;
	Point2<T> position;
};

typedef Rectangle<int> RectI;
typedef Rectangle<unsigned int> RectU;
typedef Rectangle<float> RectF;
typedef Rectangle<size_t> RectL;

#endif /* defined(__SpaceJunk__geometry__) */
