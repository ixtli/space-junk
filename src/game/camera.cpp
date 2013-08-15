//
//  camera.cpp
//  SpaceJunk
//
//  Created by ixtli on 8/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "renderer.h"
#include "camera.h"

Camera::Camera()

{}

Camera::~Camera()
{
	
}

bool Camera::init()
{
	return true;
}

void Camera::update(const Size2I &bounds)
{
	GLfloat aspect = 1.0f * bounds.width / bounds.height;
	
	glm::mat4 model, proj, view, rotation;
	
	model = glm::mat4(1.0f);
	
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f),
										 glm::vec3(0.0f, 0.0f, 0.0f),
										 glm::vec3(0.0f, 1.0f, 0.0f));
	
	proj = glm::perspective(45.0f, aspect, 0.1f, 50.0f);
	
	rotation = glm::rotate(glm::mat4(1.0f), 15.0f, glm::vec3(1.0, 1.0, 0.0));
	
	_matrix = proj * view * model * rotation;
}


