//
//	colorRectLayer.cpp
//	SpaceJunk
//
//	Created by Ixtli on 5/24/13.
//	Copyright (c) 2013 ixtli. All rights reserved.
//

#include "colorRectLayer.h"

ColorRectLayer::ColorRectLayer(bool dynamic) :

RectLayer(dynamic),
_list(NULL),
_verts(NULL),
_initialized(false),
_dirty(false)

{ }


ColorRectLayer::~ColorRectLayer()
{
	if (_list) delete [] _list;
	if (_verts) delete [] _verts;
}

bool ColorRectLayer::init(GLfloat depth, GLuint rectCount)
{
	if (!RectLayer::init(depth, rectCount))
		return false;
	
	_list = new ColorRect* [rectCount];
	
	if (!_list)
	{
		error("Couldn't initialize list.");
		return false;
	}
	
	_usedRects = 0;
	
	return true;
}

bool ColorRectLayer::addRect(ColorRect* r)
{
	if (_usedRects >= _maxRects)
	{
		warn("Too many rects.");
		return false;
	}
	
	// Save, configure and update
	_list[_usedRects] = r;
	r->index = _usedRects;
	_usedRects++;
	_quadLayer.usedQuads(_usedRects);
	listChanged();
	
	return true;
}

bool ColorRectLayer::removeRect(const ColorRect& r)
{
	if (r.index >= _usedRects)
	{
		warn("Out of bounds.");
		return false;
	}
	
	if (&r != _list[r.index])
	{
		warn("Out of sync.");
		return false;
	}
	
	for (GLuint i = r.index + 1; i < _usedRects; i++)
	{
		_list[i - 1] = _list[i];
		_list[i - 1]->index = i - 1;
	}
	
	_usedRects--;
	_quadLayer.usedQuads(_usedRects);
	listChanged();
	
	return true;
}

void ColorRectLayer::updateRect(const ColorRect &r)
{
	if (r.index >= _usedRects)
	{
		warn("Out of bounds.");
		return;
	}
	
	updateVertsForIndex(r.index);
}

inline void ColorRectLayer::updateVertsForIndex(GLuint index)
{
	GLuint v = index * 4;
	
	// Bottom left
	_verts[v].location.x = _list[index]->rect.position.x;
	_verts[v].location.y = _list[index]->rect.position.y +
		_list[index]->rect.bounds.height;
	
	_verts[v].location.z = _depth + _list[index]->depthOffset;
	_verts[v++].color = _list[index]->color;
	
	// Bottom Right
	_verts[v].location.x = _list[index]->rect.position.x +
		_list[index]->rect.bounds.width;
	_verts[v].location.y = _list[index]->rect.position.y +
		_list[index]->rect.bounds.height;
	
	_verts[v].location.z = _depth + _list[index]->depthOffset;
	_verts[v++].color = _list[index]->color;

	// Top Left
	_verts[v].location.x = _list[index]->rect.position.x;
	_verts[v].location.y = _list[index]->rect.position.y;
	
	_verts[v].location.z = _depth + _list[index]->depthOffset;
	_verts[v++].color = _list[index]->color;
	
	// Top Right
	_verts[v].location.x = _list[index]->rect.position.x +
		_list[index]->rect.bounds.width;
	_verts[v].location.y = _list[index]->rect.position.y;
	
	_verts[v].location.z = _depth + _list[index]->depthOffset;
	_verts[v++].color = _list[index]->color;
	
	listChanged();
}

void ColorRectLayer::commit()
{
	if (!_initialized)
	{
		initLayer();
	}
	
	if (!_dirty)
		return;
	
	_quadLayer.update(_verts);
	
	_dirty = false;
}

bool ColorRectLayer::initLayer()
{
	_verts = new ColorVertex[_maxRects * 4];
	
	if (!_verts)
	{
		error("Couldn't initialize verts.");
		return false;
	}
	
	// Init verts
	if (_usedRects)
	{
		for (GLuint i = 0; i < _usedRects; i++)
		{
			updateVertsForIndex(i);
		}
	} else {
		warn("Initializing with no rects.");
	}
	
	if (!_quadLayer.init(_maxRects, SOLID_QUAD_SHADER, _verts))
	{
		return false;
	}
	
	_quadLayer.usedQuads(_usedRects);
	
	_initialized = true;
	_dirty = false;
	return true;
}

