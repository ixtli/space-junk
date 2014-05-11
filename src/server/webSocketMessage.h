//
//  webSocketServer.h
//  SpaceJunk
//
//  Created by ixtli on 5/4/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__webSocketMessage__
#define __SpaceJunk__webSocketMessage__

#include "httpRequestHeaders.h"

class WebSocketMessage
{
public:
	
	WebSocketMessage(int fileDescriptor);
	~WebSocketMessage();
	
	bool init();
	bool read();
	
	inline size_t messageLength() const { return _messageLength; };
	inline const char* const message() const { return _message; };
	inline bool complete() const { return _complete; };
	
	void clearMessage();
	
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
	} WSHeader;
	
	int _fileDescriptor;
	char* _message;
	size_t _messageLength;
	bool _complete;
	
	HTTPRequestHeaders _handshakeHeaders;
	
	ssize_t readBytes(size_t count, void* loc);
	
	void addToMessage(const char* msg, size_t len);
	
	void sendPong(const char* msg);
	void sendHandshake();
	
	bool isControlFrame(const WSHeader& header);
	bool isDataFrame(const WSHeader& header);
};

#endif /* defined(__SpaceJunk__webSocketMessage__) */
