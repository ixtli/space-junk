//
//  SpaceJunkAppDelegate.h
//  SpaceJunk
//
//  Created by ixtli on 8/7/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#import <dispatch/dispatch.h>

#import <Cocoa/Cocoa.h>

#import "SpaceJunkGLView.h"

@interface SpaceJunkAppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;
@property (assign) IBOutlet SpaceJunkGLView *view;
@property (nonatomic, strong) dispatch_source_t timer;

@end
