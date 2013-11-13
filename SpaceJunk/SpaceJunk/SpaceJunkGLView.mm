//
//  SpaceJunkGLView.m
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#import "environment.h"

#import "SpaceJunkGLView.h"

@interface SpaceJunkGLView (PrivateMethods)
- (void) initGL;
- (void) drawView;
@end

@implementation SpaceJunkGLView

@synthesize resized;

#pragma mark -
#pragma mark CVDisplayLink methods

// This is the renderer output callback function
static CVReturn dispLinkCallback(CVDisplayLinkRef displayLink,
																 const CVTimeStamp* now,
																 const CVTimeStamp* outputTime,
																 CVOptionFlags flagsIn,
																 CVOptionFlags* flagsOut,
																 void* displayLinkContext)
{
	// Cast the view
	SpaceJunkGLView* v = (__bridge SpaceJunkGLView*)displayLinkContext;
	
	// There is no autorelease pool when this method is called because it will be
	// called from a background thread. It's important to create one or you will
	// leak objects. With ARC, there's a convenient block for this!
	@autoreleasepool {
		[v drawView];
	}
	
	return kCVReturnSuccess;
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
	// This does not update a visible framebuffer, so other contexts can be
	// current while it is happening
	Environment::updateRenderables();
	
	[[self openGLContext] makeCurrentContext];
	
	if (resized)
	{
		NSSize size = [self bounds].size;
		Environment::viewResize((unsigned)round(size.width),
														(unsigned)round(size.height));
		resized = false;
	}
	
	Environment::render();
	
	CGLFlushDrawable((CGLContextObj)[[self openGLContext] CGLContextObj]);
}

- (void) dealloc
{
	[self stopDrawing];
	CVDisplayLinkRelease(displayLink);
	displayLink = NULL;
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
