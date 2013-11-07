//
//  SpaceJunkGLView.m
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#import "SpaceJunkGLView.h"

#include "bridge-osx.h"

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
		[[self openGLContext] makeCurrentContext];
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
	CVDisplayLinkSetOutputCallback(displayLink, &dispLinkCallback,
																 (__bridge void *)(self));
	
	// Set the display link for the current renderer
	CGLContextObj cglContext = (CGLContextObj)[[self openGLContext] CGLContextObj];
	
	CGLPixelFormatObj cglPixelFormat = (CGLPixelFormatObj)[[self pixelFormat]
																												 CGLPixelFormatObj];
	CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink,
																										cglContext,
																										cglPixelFormat);
}

- (void) windowWillClose:(NSNotification*)notification
{
	// Stop the display link when the window is closing because default
	// OpenGL render buffers will be destroyed.  If display link continues to
	// fire without renderbuffers, OpenGL draw calls will set errors.
	[self stopDrawing];
}

- (void) initGL
{
	[[self openGLContext] makeCurrentContext];
	
	// Causes buffer swaps to sync with vertical refresh
	GLint swapInt = 1;
	[[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
}

- (void) renewGState
{
	// Called whenever graphics state updated (such as window resize)
	
	// OpenGL rendering is not synchronous with other rendering on the OSX.
	// Therefore, call disableScreenUpdatesUntilFlush so the window server
	// doesn't render non-OpenGL content in the window asynchronously from
	// OpenGL content, which could cause flickering.  (non-OpenGL content
	// includes the title bar and drawing done by the app with other APIs)
	[[self window] disableScreenUpdatesUntilFlush];
	
	[super renewGState];
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
		resizeView((unsigned)round(rect.size.width), (unsigned)round(rect.size.height));
		resized = false;
	}
	
	render();
	
	CGLFlushDrawable((CGLContextObj)[[self openGLContext] CGLContextObj]);
}

- (void) dealloc
{
	[self stopDrawing];
	CVDisplayLinkRelease(displayLink);
}

#pragma mark -
#pragma mark Useful public helper methods

- (void)resumeDrawing
{
	if (displayLink)
	{
		// Activate the display link
		CVDisplayLinkStart(displayLink);
	}
}

- (void)stopDrawing
{
	if (displayLink)
	{
		CVDisplayLinkStop(displayLink);
	}
}

@end
