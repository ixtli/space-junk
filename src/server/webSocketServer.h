//
//  webSocketServer.h
//  SpaceJunk
//
//  Created by ixtli on 5/4/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__webSocketServer__
#define __SpaceJunk__webSocketServer__

#include <sys/socket.h>

class WebSocketMessage
{
public:
	WebSocketMessage(int fileDescriptor);
	~WebSocketMessage();
	
	void read();
	
private:
	
	typedef enum
	{
		CONTINUATION,
		TEXT,
		BINARY,
		NON_CONTROL_RESERVED_1,
		NON_CONTROL_RESERVED_2,
		NON_CONTROL_RESERVED_3,
		NON_CONTROL_RESERVED_4,
		CONNECTION_CLOSED,
		PING,
		PONG,
		CONTROL_RESERVED_1,
		CONTROL_RESERVED_2,
		CONTROL_RESERVED_3,
		CONTROL_RESERVED_4
	} OpCodes;
	
	typedef struct
	{
		unsigned int fin : 1;
		unsigned int reserved : 3;
		unsigned int opCode : 4;
		unsigned int mask : 1;
		unsigned int payloadLength : 7;
	} Header;
	
	// Message metadata
	Header _preamble;
	unsigned long _totalPayloadLength;
	
	
	int _fileDescriptor;
	
	ssize_t readBytes(size_t count, void* loc);
};



#endif /* defined(__SpaceJunk__webSocketServer__) */
