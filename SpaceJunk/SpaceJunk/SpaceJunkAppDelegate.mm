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

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
	// Init the game environment
	Environment::getInstance()->init();
	
	// Start drawing and firing updates
	[_view resumeDrawing];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
	return YES;
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
	[_view stopDrawing];
	Environment::getInstance()->destroy();
}

@end
