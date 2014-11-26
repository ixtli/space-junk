//
//  uiTexturedRectElement.h
//  SpaceJunk
//
//  Created by ixtli on 11/25/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiTexturedRectElement__
#define __SpaceJunk__uiTexturedRectElement__

#include "vertexFormats.h"
#include "uiElement.h"

class UITexturedRectElement : public UIElement
{
public:
	
	UITexturedRectElement();
	
	inline void textureWidth(float tw) { _texSize.x = tw; makeDirty(); };
	inline void textureHeight(float th) { _texSize.y = th; makeDirty(); };
	
	inline void u(float _u) { _texCoord.x = _u; makeDirty(); };
	inline void v(float _v) { _texCoord.y = _v; makeDirty(); };
	void uv(float _u, float _v);
	
	void updateVerts(GLfloat depth, TextureVertex* verts) const;
	
private:
	
	Point2F _texCoord;
	Point2F _texSize;
	
};

#endif /* defined(__SpaceJunk__uiTexturedRectElement__) */
