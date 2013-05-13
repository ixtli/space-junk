//
//  SpaceJunkGLRenderer.m
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#import "SpaceJunkGLRenderer.h"

@implementation SpaceJunkGLRenderer

- (void) render
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

- (id) initWithFBOName:(GLuint)name
{
	self = [super init];
	
	if (!self)
	{
		return self;
	}
	
	NSLog(@"%s %s", glGetString(GL_RENDERER), glGetString(GL_VERSION));
	
	// Save the default VBO
	defaultFBOName = name;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	
	return self;
}

- (void) resizeWithWidth:(GLsizei)width andHeight:(GLsizei)height
{
	glBindFramebuffer(GL_FRAMEBUFFER, defaultFBOName);
	glViewport(0, 0, width, height);
}

@end
