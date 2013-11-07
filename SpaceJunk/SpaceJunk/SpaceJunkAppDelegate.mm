//
//  SpaceJunkAppDelegate.m
//  SpaceJunk
//
//  Created by ixtli on 8/7/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "environment.h"
#include "bridge-osx.h"

#import "SpaceJunkAppDelegate.h"

static const uint64_t gameUpdateInterval = 16ull * NSEC_PER_MSEC; // ~60fps
static const uint64_t gameUpdateLeeway = 2ull * NSEC_PER_MSEC; // 2ms ?

@implementation SpaceJunkAppDelegate

- (bool)initializeGameUpdateTimer
{
	// All app initialization is complete: start game events
	dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
	self.timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
	
	if (!self.timer)
	{
		return false;
	}
	
	dispatch_source_set_timer(self.timer,
														dispatch_walltime(NULL, 0),
														gameUpdateInterval,
														gameUpdateLeeway);
	
	dispatch_source_set_event_handler_f(self.timer, updateGameEvent);
	
	return true;
}

- (void)resumeGameUpdates
{
	dispatch_resume(self.timer);
}

- (void)stopGameUpdates
{
	dispatch_source_cancel(self.timer);
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
	// Init the game environment
	Environment::getInstance()->init();
	
	// Start the async game timer
	if (![self initializeGameUpdateTimer])
	{
		NSLog(@"Problem creating the dispatch source for game events. Aborting.");
		return;
	}
	
	// Start drawing and firing updates
	[_view resumeDrawing];
	[self resumeGameUpdates];
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
	[self stopGameUpdates];
	[_view stopDrawing];
}

@end
