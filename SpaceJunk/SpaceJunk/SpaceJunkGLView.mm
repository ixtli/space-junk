//
//  SpaceJunkGLView.m
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#import "SpaceJunkGLView.h"

#include "engine.h"
#include "renderer.h"

@interface SpaceJunkGLView (PrivateMethods)
- (void) initGL;
- (void) drawView;
@end

@implementation SpaceJunkGLView

@synthesize resized;

#pragma mark -
#pragma mark CVDisplayLink methods

- (CVReturn) getFrameForTime:(const CVTimeStamp*)outputTime
{
	// There is no autorelease pool when this method is called because it will be
	// called from a background thread. It's important to create one or you will
	// leak objects. With ARC, there's a convenient block for this!
	@autoreleasepool {
		[self drawView];
	}
	
	return kCVReturnSuccess;
}

// This is the renderer output callback function
static CVReturn dispLinkCallback(CVDisplayLinkRef displayLink,
																 const CVTimeStamp* now,
																 const CVTimeStamp* outputTime,
																 CVOptionFlags flagsIn,
																 CVOptionFlags* flagsOut,
																 void* displayLinkContext)
{
	return [(__bridge SpaceJunkGLView*)displayLinkContext
					getFrameForTime:outputTime];
}

#pragma mark -
#pragma mark NSOpenGLView methods

- (void) awakeFromNib
{
	
	NSOpenGLPixelFormatAttribute attrs[] =
	{
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, 24,
		NSOpenGLPFAOpenGLProfile,
		NSOpenGLProfileVersion3_2Core,
		0
	};
	
	NSOpenGLPixelFormat* pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
	
	if (!pf)
	{
		NSLog(@"No OpenGL pixel format!");
	}
	
	NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil];
	
	[self setPixelFormat:pf];
	
	[self setOpenGLContext:context];
	
	
}

- (void) prepareOpenGL
{
	[super prepareOpenGL];
	
	// Make all the opengl calls to setup rendering and build objects
	[self initGL];
	
	// Create display link for all active displays
	CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
	
	// Set renderer output callback fxn
	CVDisplayLinkSetOutputCallback(displayLink,
																 &dispLinkCallback,
																 (__bridge void *)(self));
	
	// Set the display link for the current renderer
	CGLContextObj cglContext = (CGLContextObj)[[self openGLContext]
																						 CGLContextObj];
	
	CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat]
																												 CGLPixelFormatObj];
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink,
																										cglContext,
																										cglPixelFormat);
	
	// Activate the display link
	CVDisplayLinkStart(displayLink);
}

- (void) initGL
{
	[[self openGLContext] makeCurrentContext];
	
	// Causes buffer swaps to sync with vertical refresh
	GLint swapInt = 1;
	[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
	
	// Init our renderer. Use zero for the default FBO
	// N.B.: Not appropriate for iOS
	Renderer::getInstance()->init(0);
	
	// Init the engine
	Engine::getInstance()->init();
	
}

- (void) reshape
{
	// N.B.: This method gets called BEFORE drawView on view instantiation!
	[super reshape];
	
	// CVDisplayLink draws on a secondary thread, instead of wasting time with
	// locking, just service the rect size change whenever we can, since it's
	// something that wont happen often and doesn't need to look good.
	
	resized = true;
}

- (void) drawView
{
	[[self openGLContext] makeCurrentContext];
	
	if (resized)
	{
		NSRect rect = [self bounds];
		Renderer::getInstance()->
            resize(Size2Di(rect.size.width, rect.size.height));
		resized = false;
	}
	
	Engine::getInstance()->update();
	
	Renderer::getInstance()->render();
	
	CGLFlushDrawable((CGLContextObj)[[self openGLContext] CGLContextObj]);
}

- (void) dealloc
{
	CVDisplayLinkStop(displayLink);
	CVDisplayLinkRelease(displayLink);
}

@end
