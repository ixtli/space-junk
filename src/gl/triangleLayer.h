//
//  triangleLayer.h
//  SpaceJunk
//
//  Created by ixtli on 5/24/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__triangleLayer__
#define __SpaceJunk__triangleLayer__

#include "shaderManager.h"
#include "triangleBuffer.h"

class Layer
{
public:
	
	Layer();
	~Layer();
	
	bool init();
	
	inline void draw() const
	{
		
		_buffer.draw();
	};
	
private:
	
	
	TriangleBuffer _buffer;
	
};

#endif /* defined(__SpaceJunk__triangleLayer__) */
