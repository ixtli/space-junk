//
//  camera.cpp
//  SpaceJunk
//
//  Created by ixtli on 8/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//


#include "easing.h"
#include "renderer.h"
#include "camera.h"

Camera::Camera() :

_matrix(1.0f),
_rotation(1.0f),
_perspective(45.0f)

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

void Camera::rotate(GLfloat angle)
{
	_rotation = glm::rotate(_rotation, angle, glm::vec3(1.0, 1.0, 0.0));
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
