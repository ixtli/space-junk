//
//  SpaceJunkGLRenderer.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SpaceJunkGLRenderer : NSObject {
	
	GLuint defaultFBOName;
	
}

- (id) initWithFBOName: (GLuint)name;
- (void) render;
- (void) resizeWithWidth: (GLsizei)width andHeight: (GLsizei)height;

@end
