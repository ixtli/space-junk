//
//  camera.h
//  SpaceJunk
//
//  Created by ixtli on 8/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__camera__
#define __SpaceJunk__camera__

#include "chronoUtil.h"
#include "geometry.h"

class Camera
{
public:
	
	Camera();
	~Camera();
	
	bool init();
	void updateScreenBounds(const Size2I &bounds);
	void perspectiveAngle(GLfloat angle);
	void rotate(GLfloat angle, sj_time_t duration);
	void rotate(GLfloat angle);
	void lookAt(const Point3F &loc);
	
	void update(sj_time_t dt);
	
	inline const glm::mat4& getMatrix() const { return _matrix; };
	
	// Getters
	inline GLfloat perspectiveAngle() const { return _perspective; };
	
private:
	
	void updateMatrix();
	
	GLfloat _perspective, _aspect;
	
	glm::mat4 _view, _projection, _rotation, _matrix;
	
	GLfloat _rotationDuration, _rotationTimeAccumulator;
	sj_time_t _panDuration, _panTimeAccumulator;
};

#endif /* defined(__SpaceJunk__camera__) */
