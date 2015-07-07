//
//  camera.cpp
//  SpaceJunk
//
//  Created by ixtli on 8/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//


#include "../engine/easing.h"
#include "../gl/renderer.h"
#include "./camera.h"

Camera::Camera() :

_matrix(1.0f),
_rotation(1.0f),
_perspective(45.0f),
_rotationDuration(0.0f)

{}

Camera::~Camera()
{
	
}

bool Camera::init()
{
	_view = glm::lookAt(glm::vec3(2.0f, 5.0f, 10.0f),
											glm::vec3(0.0f, 0.0f, 0.0f),
											glm::vec3(0.0f, 1.0f, 0.0f));
	
	return true;
}

void Camera::updateScreenBounds(const Size2I &bounds)
{
	GLfloat newAspect = 1.0f * bounds.width / bounds.height;
	
	if (_aspect == newAspect) return;
	
	_aspect = newAspect;
	_projection = glm::perspective(_perspective, _aspect, 0.1f, 50.0f);
	updateMatrix();
}

void Camera::rotate(GLfloat angle, sj_time_t duration)
{
	_rotationDuration = duration;
	_rotationTimeAccumulator = 0;
}

void Camera::rotate(GLfloat angle)
{
	_rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0, 1.0, 0.0));
	updateMatrix();
}

void Camera::perspectiveAngle(GLfloat angle)
{
	if (_perspective == angle) return;
	
	_perspective = angle;
	_projection = glm::perspective(_perspective, _aspect, 0.1f, 50.0f);
	updateMatrix();
}

void Camera::updateMatrix()
{
	_matrix = _projection * _view * _rotation;
}

void Camera::update(sj_time_t dt)
{
	if (_rotationDuration > _rotationTimeAccumulator)
	{
		_rotationTimeAccumulator += dt;
		GLfloat out = easeInOutQuad<GLfloat>(_rotationTimeAccumulator,
																				 _rotationDuration);
		
		rotate(180.0f * out);
	}
}

