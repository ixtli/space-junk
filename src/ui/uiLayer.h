//
//  uiLayer.h
//  SpaceJunk
//
//  Created by ixtli on 5/30/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiLayer__
#define __SpaceJunk__uiLayer__

#include "uiElement.h"
#include "rectLayer.h"

class UILayer
{
public:
	
	UILayer(RectLayer* layer);
	~UILayer();
	
	inline void draw() const { _layer->draw(); };
	
	inline void update()
	{
		for (size_t i = 0; i < _elementCount; i++)
			_elementList[i]->update();
		
		_layer->commit();
	}
	
	inline void depth(GLfloat d) { _depth = d; };
	inline GLfloat depth() const { return _depth; };
	
	bool addElement(UIElement* e);
	bool removeElement(UIElement* e);
	
protected:
	
	UIElement** _elementList;
	size_t _elementCount;
	
	GLfloat _depth;
	
private:
	
	RectLayer* _layer;
	
};

#endif /* defined(__SpaceJunk__uiLayer__) */
