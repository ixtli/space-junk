//
//  cubescene.h
//  SpaceJunk
//
//  Created by ixtli on 8/11/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__cubeScene__
#define __SpaceJunk__cubeScene__

#include "cubeBuffer.h"
#include "cube.h"

class CubeScene
{
public:
	
	inline static CubeScene* instance() { return &_instance; };
	
	bool init(const Point3i &size);
	
private:
	
	CubeScene();
	~CubeScene();
	
	static CubeScene _instance;
	
	Point3i _size;
	CubeBuffer _buffer;
	Cube* _cubes;
	
	
};

#endif /* defined(__SpaceJunk__cubescene__) */
