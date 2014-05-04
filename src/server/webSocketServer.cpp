//
//  webSocketServer.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/4/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "webSocketServer.h"

#include <cstdint>

WebSocketMessage::WebSocketMessage() :

_message(NULL),
_messageLength(0),
_complete(false)

{}

WebSocketMessage::~WebSocketMessage()
{
	if (_message || _messageLength)
	{
		delete [] _message;
	}
}

ssize_t WebSocketMessage::readBytes(int fd, size_t count, void *loc)
{
	ssize_t bytesRead = recv(fd, loc, count, 0);
	
	if (bytesRead <= 0)
	{
		// Got error connection closed by client
		if (bytesRead == 0)
		{
			info("Socket %d hung up.", fd);
		} else {
			error("recv");
		}
	}
	
	return bytesRead;
}

bool WebSocketMessage::read(int fileDescriptor)
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
	
	// The message preamble
	Header preamble;
	
	// Handle data from a client
	if (!readBytes(fileDescriptor, sizeof(preamble), &preamble))
		return false;
	
	// Will eventually contain the total byte size of message payload
	unsigned long totalPayloadLength = 0;
	
	// preamble some magic to be done when determining the size of the message
	if (preamble.payloadLength <= 125)
	{
		totalPayloadLength = preamble.payloadLength;
		
	} else if (preamble.payloadLength == 126) {
		
		// the following 2 bytes interpreted as a	16-bit unsigned integer are the
		// payload length.
		uint_fast16_t extraLen;
		
		if(!readBytes(fileDescriptor, sizeof(extraLen), &extraLen))
			return false;
		
		totalPayloadLength = extraLen;
		
	} else {
		
		// the following 8 bytes interpreted as a 64-bit unsigned integer (the
		// most significant bit MUST be 0) are the payload length.
		uint_fast64_t extraLen;
		
		if(!readBytes(fileDescriptor, sizeof(extraLen), &extraLen))
			return false;
		
		totalPayloadLength = extraLen;
	}
	
	// Under the current version of the protocol, all payloads are masked, but
	// it's still technically possible for the client to send unmasked data
	uint_fast32_t maskingKey;
	
	// The 32bit masking key is not present if the mask bit isn't set
	if (preamble.mask)
	{
		if (!readBytes(fileDescriptor, sizeof(maskingKey), &maskingKey))
			return false;
	}
	
	// Read the message
	char msg[totalPayloadLength + 1];
	msg[totalPayloadLength] = '\0';
	
	// Make sure the expected amount of bytes was read
	ssize_t count = readBytes(fileDescriptor, totalPayloadLength, msg);
	
	info("C: %u\tM: %s\t%lu/%lu bytes:",
			 preamble.opCode,
			 (preamble.mask ? "yes" : "no"),
			 count,
			 totalPayloadLength);
	
	// This would count as a violation of the standard.
	if (count < totalPayloadLength)
	{
		error("Less bytes read than expected.");
		return false;
	}
	
	if (preamble.fin)
	{
		_complete = true;
		info("Message complete.");
	}
	
	// This function appends a '\0' so only provide the raw string
	addToMessage(msg, totalPayloadLength);
	
	return true;
}

void WebSocketMessage::addToMessage(const char *msg, size_t len)
{
	size_t newLength = _messageLength + len;
	char* newMessage = new char[newLength + 1];
	
	// Safety
	if (_messageLength && _message)
	{
		memcpy(newMessage, _message, _messageLength);
		// We nolonger need the old one
		delete [] _message;
	}
	
	memcpy(newMessage + _messageLength, msg, len);
	newMessage[newLength] = '\0';
	
	_messageLength = newLength;
	_message = newMessage;
}

