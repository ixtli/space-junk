//
//  cubeBuffer.h
//  SpaceJunk
//
//  Created by ixtli on 8/11/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__cubeBuffer__
#define __SpaceJunk__cubeBuffer__

class Cube;

class CubeBuffer
{
public:
	
	CubeBuffer();
	~CubeBuffer();
	
	bool init(const Cube* cubes, size_t count);
	
private:
	
	size_t _count;
	
};

#endif /* defined(__SpaceJunk__cubeBuffer__) */
