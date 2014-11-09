//
//  webSocketMessage.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/4/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include <sys/socket.h>
#include <netinet/in.h>

#include "webSocketMessage.h"

#include "randUtil.h"

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

bool WebSocketMessage::sendPong(const void* msg, size_t len) const
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
		return false;
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
		return false;
	}
	
	return true;
}

bool WebSocketMessage::sendClose()
{
	/* (When sending a Close frame in response, the endpoint typically echos the
   status code it received.) */
	
	uint_fast16_t message[2];
	
	// Create the preamble (2 byte short)
	message[0] = makePreamble(true, false, CONNECTION_CLOSED, 2);
	
	// Write the close status as a network byte order short
	message[1] = _closeStatusCode;
	
	// Big endian
	HTONS(message[1]);
	
	// Total is four bytes
	if (send(_fileDescriptor, message, 4, 0) == -1)
	{
		error("send()");
		return true;
	}
	
	return false;
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
	 
	 "When encoded on the wire, the most significant bit is the leftmost"
	 
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
	
	// In the above figure, the MOST SIGNIFICANT BIT is on the left. This means
	// that 'fin' is supposed to be the 16th bit. To make sure this happens we
	// need to make sure we're converting from network byte order (big) to host
	// which, in the case of little-endian, will result in flipping the bytes.
	NTOHS(rawPreamble);
	
	// Select the lower 7 bits of the message for payload length
	uint_fast8_t payloadLength = rawPreamble & 0x007F;
	
	// Whether or not the message is masked (it should be) is determined by the
	// bit in the 8th position.
	bool masked = rawPreamble & 0x0080;
	
	// If this is to be the last message for this operation, the MSB will be on
	_complete = rawPreamble & 0x8000;
	
	// The operation code is second most significant nybble.
	unsigned int opCode = (rawPreamble >> 8) & 0x000F;
	
	// Might be useful information
	info("%s frame", kOpCodeNames[opCode]);
	
	// Will eventually contain the total byte size of message payload
	size_t totalPayloadLength = 0;
	
	// preamble some magic to be done when determining the size of the message
	if (payloadLength <= 125)
	{
		// "if 0-125 [bytes], that is the payload length"
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
			NTOHS(closeStatusCode);
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

bool WebSocketMessage::sendMessage(const char *msg, size_t length) const
{
	// 2 byte header
	size_t headerSize = 2;
	
	// The top 7 bytes of the preamble
	uint_fast8_t payloadLength = 0;
	
	if (length < 126)
	{
		payloadLength = (uint_fast8_t)length;
	} else if (length <= UINT_FAST16_MAX) {
		// 126 is code for size described as a 16bit uint
		payloadLength = 126;
		headerSize += 2;
	} else {
		// 127 is code for size described as a 64bit uint
		payloadLength = 127;
		headerSize += 8;
	}
	
	// The message itself
	size_t totalMessageSize = headerSize + length;
	char message[totalMessageSize];

	// frame is 'finished' and unmasked
	uint_fast16_t preamble = makePreamble(true, false, TEXT, payloadLength);
	
	// The first two bytes are the websocket preamble
	*((uint_fast16_t*)&message) = preamble;
	
	// Set the size information after the header if necessary
	if (length > 125 && length <= UINT_FAST16_MAX)
	{
		// Otherwise the already complex next line looks even worse
		uint_fast16_t shortLength = (uint_fast16_t)length;
		
		// The SECOND 16 bits into the message is the size as a uint
		uint_fast16_t* extendedSize = (uint_fast16_t*) &message[2];
		*extendedSize = HTONS(shortLength);
	} else if (length > UINT_FAST16_MAX) {
		
		// In this case, the 64 bits following the payload are a long uint
		// that describe the payload length
		uint_fast64_t* extendedSize = (uint_fast64_t*) &message[2];
		*extendedSize = length;
		
		HTONLL(*extendedSize);
	}

	// Copy the message
	memcpy(&message[headerSize], msg, length);
	
	// Send the actual message
	if (send(_fileDescriptor, message, totalMessageSize, 0) == -1)
	{
		error("send()");
		return false;
	}
	
	return true;
}

uint_fast16_t WebSocketMessage::makePreamble(bool fin, bool mask, OpCodes op,
																						 uint_fast8_t size)
{
	/*
	 Remember that this diagram is big endian
	 
	  0                   1
	  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
	 +-+-+-+-+-------+-+-------------+
	 |F|R|R|R| opcode|M| Payload len |
	 |I|S|S|S|  (4)  |A|     (7)     |
	 |N|V|V|V|       |S|             |
	 | |1|2|3|       |K|             |
	 +-+-+-+-+-------+-+-------------+
	 
	 */
	
	// Remember that the size can't have a bit flipped in the 128 place
	uint_fast16_t ret = size > 127 ? 127 : size;

	// Is this the last frame in this operation?
	if (fin) ret |= 1 << 15;
	
	// Is the payload data masked? (server should not mask data being sent
	// to the client.)
	if (mask) ret |= 1 << 7;
	
	// Opcode
	ret |= op << 8;
	
	return HTONS(ret);
}


