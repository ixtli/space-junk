//
//  camera.h
//  SpaceJunk
//
//  Created by ixtli on 8/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__camera__
#define __SpaceJunk__camera__

#include "geometry.h"

class Camera
{
public:
	
	Camera();
	~Camera();
	
	bool init();
	void update(const Size2I &bounds);
	
	inline const glm::mat4& getMatrix() const { return _matrix; };
	
private:
	
	glm::mat4 _matrix;
	
};

#endif /* defined(__SpaceJunk__camera__) */
