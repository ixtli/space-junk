//
//  SpaceJunkGLView.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//


#import <OpenGL/gl.h>

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

@interface SpaceJunkGLView : NSOpenGLView {
	
	CVDisplayLinkRef displayLink;
	
}

@property (atomic) BOOL resized;

@end
