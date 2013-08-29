//
//  SpaceJunkGLView.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#import <QuartzCore/CVDisplayLink.h>

@interface SpaceJunkGLView : NSOpenGLView {
	
	CVDisplayLinkRef displayLink;
	
	@private
	
	
	
}

@property (atomic) BOOL resized;

@end
