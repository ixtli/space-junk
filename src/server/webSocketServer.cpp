//
//  webSocketServer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/4/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "webSocketServer.h"

#include <cstdint>

WebSocketMessage::WebSocketMessage(int fileDescriptor) :

_fileDescriptor(fileDescriptor)

{}

WebSocketMessage::~WebSocketMessage()
{
	
}

ssize_t WebSocketMessage::readBytes(size_t count, void *loc)
{
	ssize_t bytesRead = recv(_fileDescriptor, loc, count, 0);
	
	if (bytesRead <= 0)
	{
		// Got error connection closed by client
		if (bytesRead == 0)
		{
			info("Socket %d hung up.", _fileDescriptor);
		} else {
			error("recv");
		}
	}
	
	return bytesRead;
}

void WebSocketMessage::read()
{
	/*
	 Protocol frame map:
	 http://tools.ietf.org/html/rfc6455#page-22
	 
	  0                   1                   2                   3
	  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
	 +-+-+-+-+-------+-+-------------+-------------------------------+
	 |F|R|R|R| opcode|M| Payload len |    Extended payload length    |
	 |I|S|S|S|  (4)  |A|     (7)     |             (16/64)           |
	 |N|V|V|V|       |S|             |   (if payload len==126/127)   |
	 | |1|2|3|       |K|             |                               |
	 +-+-+-+-+-------+-+-------------+ - - - - - - - - - - - - - - - +
	 |     Extended payload length continued, if payload len == 127  |
	 + - - - - - - - - - - - - - - - +-------------------------------+
	 |                               |Masking-key, if MASK set to 1  |
	 +-------------------------------+-------------------------------+
	 | Masking-key (continued)       |          Payload Data         |
	 +-------------------------------- - - - - - - - - - - - - - - - +
	 :                     Payload Data continued ...                :
	 + - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - +
	 |                     Payload Data continued ...                |
	 +---------------------------------------------------------------+
	 
	 */
	
	// Handle data from a client
	if (!readBytes(sizeof(_preamble), &_preamble))
		return;
	
	// There's some magic to be done when determining the size of the message
	if (_preamble.payloadLength <= 125)
	{
		_totalPayloadLength = _preamble.payloadLength;
		
	} else if (_preamble.payloadLength == 126) {
		
		// the following 2 bytes interpreted as a	16-bit unsigned integer are the
		// payload length.
		uint_fast16_t extraLen;
		
		if(!readBytes(sizeof(extraLen), &extraLen))
			return;
		
		_totalPayloadLength = extraLen;
		
	} else {
		
		// the following 8 bytes interpreted as a 64-bit unsigned integer (the
		// most significant bit MUST be 0) are the payload length.
		uint_fast64_t extraLen;
		
		if(!readBytes(sizeof(extraLen), &extraLen))
			return;
		
		_totalPayloadLength = extraLen;
	}
	
	// Under the current version of the protocol, all payloads are masked, but
	// it's still technically possible for the client to send unmasked data
	uint_fast32_t maskingKey;
	
	if (_preamble.mask)
	{
		if (!readBytes(sizeof(maskingKey), &maskingKey))
			return;
	}
	
	info("WS OpCode: %u", _preamble.opCode);
	
	char msg[_totalPayloadLength + 1];
	msg[_totalPayloadLength] = '\0';
	
	ssize_t count = readBytes(_totalPayloadLength, msg);
	
	info("Read %lu / %lu bytes.",
			 _totalPayloadLength,
			 count);
	
	info("Read message: %s", msg);
}

