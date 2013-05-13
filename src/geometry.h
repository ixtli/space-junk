//
//  geometry.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__geometry__
#define __SpaceJunk__geometry__

struct UIPoint
{
	UIPoint() : top(0), left(0) {};
	UIPoint(GLuint _top, GLuint _left) : top(_top), left(_left) {};
	UIPoint(const UIPoint& p) : top(p.top), left(p.left) {};
	
	GLuint top;
	GLuint left;
};

struct UISize
{
	UISize() : width(0), height(0) {};
	UISize(GLuint _width, GLuint _height) : width(_width), height(_height) {};
 	UISize(const UISize& s) : width(s.width), height(s.height) {};
	
	GLuint width;
	GLuint height;
};

struct UIRect
{
	UIRect() : UISize(), position() {};
	UIRect(GLuint _width, GLuint _height) : UISize(_width, _height), position() {};
	UIRect(GLuint _top, GLuint _left, GLuint _width, GLuint _height) :
		UISize(_width, _height), position(_top, _left) {};
	UIRect(const UISize& s, const UIPoint& p) : UISize(s), position(p) {};
	UIRect(const UIRect& r) : UISize(r.UISize), position(r.position) {};
	
	UISize UISize;
	UIPoint position;
};

#endif /* defined(__SpaceJunk__geometry__) */
