//
//  rectLayer.h
//  SpaceJunk
//
//  Created by ixtli on 5/30/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__rectLayer__
#define __SpaceJunk__rectLayer__

#include "quadLayer.h"

template <class R, class V>
class RectLayer
{
public:
	
	static const GLuint MAX_RECTS = 0xFFFC;
	
	RectLayer(bool dynamic = false) :
	
	_quadLayer(dynamic),
	_maxRects(0),
	_usedRects(0),
	_rects(NULL),
	_verts(NULL),
	_dirty(false),
	_depth(0.0f),
	_format(NUM_SHADER_TYPES),
	_initialized(false)
	
	{ }
	
	~RectLayer()
	{
		if (_rects) delete [] _rects;
		if (_verts) delete [] _verts;
	}
	
	bool init(GLfloat depth, GLuint rectCount, ShaderFormat format)
	{
		if (!rectCount)
		{
			error("Must initialize layer with at least one rect.");
			return false;
		}
		
		if (rectCount >= MAX_RECTS)
		{
			error("A single layer can't have more than %u rects.", MAX_RECTS);
			return false;
		}
		
		// Save simple members for later use
		_depth = depth;
		_maxRects = rectCount;
		_format = format;
		
		// Initialize the pool of rects
		_rects = new R[_maxRects];
		
		if (!_rects)
		{
			error("Could not allocate rect objects.");
			return false;
		}
		
		// Initialize the verts
		_verts = new V[_maxRects * 4];
		
		if (!_verts)
		{
			error("Could not allocate verts.");
			return false;
		}
		
		return true;
	}
	
	/** @return a new rect from the pool, or null */
	R* newRect()
	{
		if (_usedRects >= _maxRects)
		{
			warn("Pool is out of rects.");
			return NULL;
		}
		
		R* ret = &_rects[_usedRects];
		ret->index(_usedRects);
		
		_usedRects++;
		_quadLayer.usedQuads(_usedRects);
		
		updateRect(ret);
		
		return ret;
	};
	
	/**
	 Remove a rect from the list.
	 Worst case: O(n), n == (_usedRects - 1)
	 @param r the rect to remove
	 @return true if successful, false otherwise
	 */
	bool removeRect(const R& r)
	{
		if (r.index() >= _usedRects)
		{
			warn("Out of bounds.");
			return false;
		}
		
		if (&r != _rects[r.index()])
		{
			warn("Out of sync.");
			return false;
		}
		
		for (GLuint i = r.index() + 1; i < _usedRects; i++)
		{
			_rects[i - 1] = _rects[i];
			_rects[i - 1]->index(i - 1);
			updateRect(_rects[i - 1]);
		}
		
		_usedRects--;
		_quadLayer.usedQuads(_usedRects);
		
		return true;
	};
	
	/**
	 Update a rect
	 @param r the rect to update
	 */
	void updateRect(const R* r)
	{
		if (r->index() >= _usedRects)
		{
			warn("Out of bounds.");
			return;
		}
		
		r->updateVerts(_depth, _verts);
		
		listChanged();
	};
	
	/** Draw the layer */
	inline void draw() const { _quadLayer.draw(); };
	
	/** @return the current amount of rects used by the layer */
	inline GLuint used() const { return _usedRects; };
	
	/** Update graphics card with changes made to the list */
	inline void commit()
	{
		if (!_dirty) return;
		
		if (_initialized)
		{
			_quadLayer.update(_verts);
			_dirty = false;
			return;
		}
		
		if (!_quadLayer.init(_maxRects, _format, _verts))
		{
			return;
		}
		
		// Start by displaying no quads
		_quadLayer.usedQuads(_usedRects);
		_initialized = true;
		_dirty = false;
	};
	
protected:
	
	/** Call whenever ther vert list is updated */
	inline void listChanged() { _dirty = true; };
	
	// State
	ShaderFormat _format;
	GLfloat _depth;
	GLuint _maxRects;
	GLuint _usedRects;
	bool _dirty;
	bool _initialized;
	
	/** The pool of rect objects. Allocate from pool to increase locality. */
	R* _rects;
	
	/** An array of pointers to verts. */
	V* _verts;
	
	QuadLayer _quadLayer;
	
};

#endif /* defined(__SpaceJunk__rectLayer__) */
