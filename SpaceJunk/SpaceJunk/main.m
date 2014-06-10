//
//  main.m
//  SpaceJunk
//
//  Created by ixtli on 8/7/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#import <Cocoa/Cocoa.h>

int main(int argc, const char * argv[])
{
	// Ignore SIG_PIPE on this thread.
	signal(SIGPIPE, SIG_IGN);
	
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	
	sa.sa_handler = SIG_IGN;
	
	if (-1 == sigaction(SIGPIPE, &sa, NULL))
	{
		perror("sigaction() failed");
	}
	
	return NSApplicationMain(argc, argv);
}
