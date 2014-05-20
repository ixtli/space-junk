//
//  webSocketMessage.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/4/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdint>

#include "webSocketMessage.h"

const char* const kOpCodeNames[] = {
	"Continuation",
	"Text",
	"Binary",
	"Non-control reserved 1",
	"Non-control reserved 2",
	"Non-control reserved 3",
	"Non-control reserved 4",
	"Non-control reserved 5",
	"Close",
	"Ping",
	"Pong",
	"Control reserved 1",
	"Control reserved 2",
	"Control reserved 3",
	"Control reserved 4",
	"Control reserved 5"
};

WebSocketMessage::WebSocketMessage(int fileDescriptor) :

_fileDescriptor(fileDescriptor),
_message(NULL),
_messageLength(0),
_complete(false)

{}

WebSocketMessage::~WebSocketMessage()
{
	clearMessage();
}

void WebSocketMessage::clearMessage()
{
	if (_message)
	{
		delete [] _message;
		_message = NULL;
	}
	
	_messageLength = 0;
}


bool WebSocketMessage::init()
{
	
	return true;
}

void WebSocketMessage::close()
{
	_closeStatusCode = 1000;
	sendClose();
}

void WebSocketMessage::sendPong(const void* msg, size_t len)
{
	/*
	 A Pong frame sent in response to a Ping frame must have identical
   "Application data" as found in the message body of the Ping frame
   being replied to.
	 
   If an endpoint receives a Ping frame and has not yet sent Pong
   frame(s) in response to previous Ping frame(s), the endpoint MAY
   elect to send a Pong frame for only the most recently processed Ping
   frame.
	 */
	
	if (len > 125)
	{
		error("Can not send control frame > 125b");
		return;
	}
	
	uint_fast8_t message[2 + len];
	
	message[0] = 0x89; // fin, opcode = pong
	message[1] = (len & 0x7F); // size of payload AND that it is NOT masked
	
	// Copy the message
	memcpy(message + 2, msg, len);
	
	// Send it back
	if (send(_fileDescriptor, message, 2 + len, 0) == -1)
	{
		error("send()");
	}
}

void WebSocketMessage::sendClose()
{
	/* (When sending a Close frame in response, the endpoint typically echos the
   status code it received.) */
	
	uint_fast8_t message[4];
	
	message[0] = 0x88; // fin, opcode = close
	message[1] = 0x2; // not masked, 2 bytes in length (status code)
	*((uint_fast16_t*)(&message[2])) = HTONS(_closeStatusCode);
	
	if (send(_fileDescriptor, message, 4, 0) == -1)
	{
		error("send()");
	}
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

bool WebSocketMessage::read()
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
	uint_fast16_t rawPreamble = 0;
	if (!readBytes(2, &rawPreamble))
		return false;

	rawPreamble = HTONS(rawPreamble);
	
	unsigned int payloadLength = rawPreamble & 0x007F;
	bool masked = rawPreamble & 0x0080;
	_complete = rawPreamble & 0x8000;
	unsigned int opCode = (rawPreamble >> 8) & 0x000F;
	
	info("%s frame", kOpCodeNames[opCode]);
	
	// Will eventually contain the total byte size of message payload
	size_t totalPayloadLength = 0;
	
	// preamble some magic to be done when determining the size of the message
	if (payloadLength <= 125)
	{
		totalPayloadLength = payloadLength;
		
	} else if (payloadLength == 126) {
		
		// the following 2 bytes interpreted as a	16-bit unsigned integer are the
		// payload length.
		uint_fast16_t extraLen = 0;
		
		if(!readBytes(sizeof(extraLen), &extraLen))
			return false;
		
		/* Multibyte length quantities are expressed in network byte order. */
		totalPayloadLength = NTOHS(extraLen);
		
	} else {
		
		// the following 8 bytes interpreted as a 64-bit unsigned integer (the
		// most significant bit MUST be 0) are the payload length.
		uint_fast64_t extraLen = 0;
		
		if(!readBytes(sizeof(extraLen), &extraLen))
			return false;
		
		/* Multibyte length quantities are expressed in network byte order. */
		totalPayloadLength = NTOHL(extraLen);
	}
	
	// Enforce the standard. (Control frames are those with MSB = 1)
	if (opCode >= 8)
	{
		if (totalPayloadLength > 125)
		{
			warn("Control frame payload is greater than 125 bytes.");
		}
	}
	
	// Under the current version of the protocol, all payloads are masked, but
	// it's still technically possible for the client to send unmasked data
	uint_fast32_t maskingKey = 0;
	
	// The 32bit masking key is not present if the mask bit isn't set
	if (masked)
	{
		if (!readBytes(sizeof(maskingKey), &maskingKey))
			return false;
	}
	
	if (opCode == CONNECTION_CLOSED)
	{
		if (totalPayloadLength)
		{
			/*
			 If there is a body, the first two bytes of the body MUST be a 2-byte
			 unsigned integer (in network byte order) representing a status code
			 */
			uint_fast16_t closeStatusCode = 0;
			readBytes(2, &closeStatusCode);
			closeStatusCode = NTOHS(closeStatusCode);
			totalPayloadLength -= 2;
		} else {
			/* Status codes in the range 0-999 are not used. */
			_closeStatusCode = 1;
		}
	}
	
	if (!totalPayloadLength)
	{
		switch (opCode)
		{
			case PING:
				sendPong(NULL, 0);
				break;
				
			case CONNECTION_CLOSED:
				sendClose();
				return false;
				
			default:
				break;
		}
		
		return true;
	}
	
	// Read the message
	unsigned char msg[totalPayloadLength + 1];
	msg[totalPayloadLength] = '\0';
	
	// Make sure the expected amount of bytes was read
	ssize_t count = readBytes(totalPayloadLength, msg);
	
	// This would count as a violation of the standard.
	if (count < totalPayloadLength)
	{
		warn("Less bytes read than expected.");
	}
	
	if (opCode == PING)
	{
		// We pass it pre-decode because the spec says that the Pong must have
		// the exact application data it received in the ping
		sendPong((char*)msg, totalPayloadLength);
	}
	
	// Only try to unmask the data if the field is marked
	if (masked)
	{
		/*
		 Octet i of the transformed data ("transformed-octet-i") is the XOR of
		 octet i of the original data ("original-octet-i") with octet at index
		 i modulo 4 of the masking key ("masking-key-octet-j"):
		 
		 j                   = i MOD 4
		 transformed-octet-i = original-octet-i XOR masking-key-octet-j
		 */
		for (size_t i = 0; i < count; i++)
		{
			msg[i] = msg[i] ^ ((uint_fast8_t*)(&maskingKey))[i % 4];
		}
	}
	
	if (opCode == CONNECTION_CLOSED)
	{
		/* Following the 2-byte integer, the body MAY contain UTF-8-encoded data
		 with value /reason/ */
		
		/* If an endpoint receives a Close frame and did not previously send a
		 Close frame, the endpoint MUST send a Close frame in response. */
		
		sendClose();
		return false;
	}
	
	// This function appends a '\0' so only provide the raw string
	addToMessage((char*)msg, count);
	
	return true;
}

void WebSocketMessage::addToMessage(const char *msg, size_t len)
{
	if (!msg || !len)
		return;
	
	size_t newLength = _messageLength + len;
	char* newMessage = new char[newLength + 1];
	
	// Safety
	if (_message)
	{
		strcpy(newMessage, _message);
		delete [] _message;
	}
	
	strcpy(newMessage + _messageLength, msg);
	newMessage[newLength] = '\0';
	
	_messageLength = newLength;
	_message = newMessage;
}

