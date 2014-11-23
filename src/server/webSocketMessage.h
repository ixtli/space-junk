//
//  webSocketServer.h
//  SpaceJunk
//
//  Created by ixtli on 5/4/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__webSocketMessage__
#define __SpaceJunk__webSocketMessage__

#include <cstdint>

class WebSocketMessage
{
public:
	
	WebSocketMessage(int fileDescriptor);
	~WebSocketMessage();
	
	bool init();
	bool read();
	void close();
	
	inline size_t messageLength() const { return _messageLength; };
	inline const char* const message() const { return _message; };
	inline bool complete() const { return _complete; };
	
	void clearMessage();
	
	bool sendMessage(const char *msg, size_t length) const;
	
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
		NON_CONTROL_RESERVED_5,
		CONNECTION_CLOSED,
		PING,
		PONG,
		CONTROL_RESERVED_1,
		CONTROL_RESERVED_2,
		CONTROL_RESERVED_3,
		CONTROL_RESERVED_4,
		CONTROL_RESERVED_5,
		NUM_OP_CODES
	} OpCodes;
	
	int _fileDescriptor;
	char* _message;
	size_t _messageLength;
	bool _complete;
	uint_fast16_t _closeStatusCode;
	
	ssize_t readBytes(size_t count, void* loc);
	
	void addToMessage(const char* msg, size_t len);
	bool sendClose();
	bool sendPong(const void* msg, uint_fast8_t len) const;
	
	static void makePreamble(unsigned char *buffer,
													 bool fin, bool mask, OpCodes op, uint_fast8_t size);
};

#endif /* defined(__SpaceJunk__webSocketMessage__) */
