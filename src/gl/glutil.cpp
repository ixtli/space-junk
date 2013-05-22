//
//  glutil.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/21/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "glutil.h"

void loadOrtho(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top,
               GLfloat near, GLfloat far, matrix4f mOut)
{
	GLfloat r_l = right - left;
	GLfloat t_b = top - bottom;
	GLfloat f_n = far - near;
	GLfloat tx = - (right + left) / (right - left);
	GLfloat ty = - (top + bottom) / (top - bottom);
	GLfloat tz = - (far + near) / (far - near);
	
	mOut[0] = 2.0f / r_l;
	mOut[1] = 0.0f;
	mOut[2] = 0.0f;
	mOut[3] = 0.0f;
	
	mOut[4] = 0.0f;
	mOut[5] = 2.0f / t_b;
	mOut[6] = 0.0f;
	mOut[7] = 0.0f;
	
	mOut[8] = 0.0f;
	mOut[9] = 0.0f;
	mOut[10] = -2.0f / f_n;
	mOut[11] = 0.0f;
	
	mOut[12] = tx;
	mOut[13] = ty;
	mOut[14] = tz;
	mOut[15] = 1.0f;
}