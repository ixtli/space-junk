//
//  SpaceJunkAppDelegate.m
//  SpaceJunk
//
//  Created by ixtli on 8/7/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "environment.h"

#import "SpaceJunkAppDelegate.h"

@implementation SpaceJunkAppDelegate

- (void)resumeGameUpdates
{
}

- (void)stopGameUpdates
{
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
	// Init the game environment
	Environment::getInstance()->init();
	
	// Start drawing and firing updates
	[_view resumeDrawing];
	[self resumeGameUpdates];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
	return YES;
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
	[self stopGameUpdates];
	[_view stopDrawing];
	Environment::getInstance()->destroy();
}

@end
