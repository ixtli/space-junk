//
//  webSocketSession.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/11/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include <sys/socket.h>
#include <stdio.h>

#include "webSocketSession.h"

#include "crypto.h"

const char* kWebSocketProtocolVerison = "13";

const char* kMagicGUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";

WebSocketSession::WebSocketSession(int fd) :

_fileDescriptor(fd),
_message(fd),
_open(false),
_handshakeHeaders()

{}

WebSocketSession::~WebSocketSession()
{
	_message.close();
}

bool WebSocketSession::init()
{
	const size_t bufferSize = 1024;
	char buffer[bufferSize];
	ssize_t bytesRead = 0;
	size_t messageLength = 0;

	char* message = NULL;
	char* oldMessage = NULL;
	
	// Since we do not know the length we have to keep reading until we're done
	// this could be arbitrarily large.
	do
	{
		bytesRead = recv(_fileDescriptor, buffer, bufferSize, 0);
		
		if (bytesRead <= 0)
		{
			// Got error connection closed by client
			if (bytesRead == 0)
			{
				info("Socket %d hung up.", _fileDescriptor);
			} else {
				error("recv");
			}
			
			return false;
		}
		
		if (message)
		{
			oldMessage = message;
		}
		
		message = new char[messageLength + bytesRead + 1];
		
		if (oldMessage)
		{
			strcpy(message, oldMessage);
			delete [] oldMessage;
		}
		
		memcpy(message, buffer, bytesRead);
		messageLength += bytesRead;
		message[messageLength] = '\0';
		
	} while (bytesRead == bufferSize);
	
	if (!messageLength)
	{
		error("No message recieved to initialize the connection.");
		return false;
	}
	
	_handshakeHeaders.init(message);
	
	delete [] message;
	
	// Are we speaking the same language?
	if (strcmp(kWebSocketProtocolVerison,
						 _handshakeHeaders.header("Sec-WebSocket-Version")))
	{
		warn("Unsupported websocket version.");
		
		return false;
	}
	
	sendHandshake();
	
	_open = true;
	
	return _open;
}

void WebSocketSession::newData()
{
	if (!_message.read())
	{
		_open = false;
	}
	
	if (_message.complete())
	{
		info("Message: %s", _message.message());
		_message.clearMessage();
	}
}

void WebSocketSession::sendHandshake()
{
	const char* key = _handshakeHeaders.header("Sec-WebSocket-Key");
	
	if (!key)
	{
		error("No Sec-WebSocket-Key header.");
		return;
	}
	
	// The encoded message goes in this buffer
	char encodedMessage[128];
	
	/*
	 the server has to take [..] the header field [Sec-WebSocket-Key] minus
   any leading and trailing whitespace) and concatenate this with the
   Globally Unique Identifier (GUID, [RFC4122]) "258EAFA5-E914-47DA-
   95CA-C5AB0DC85B11"
	 */
	size_t keyLength = strlen(key);
	size_t charCount = keyLength + strlen(kMagicGUID);
	strcpy(encodedMessage, key);
	strcpy(encodedMessage + keyLength, kMagicGUID);
	encodedMessage[charCount] = '\0';
	
	/*
	 A SHA-1 hash (160 bits) [FIPS.180-3], base64-encoded (see Section 4 of
   [RFC4648]), of this concatenation is then returned in the server's
   handshake.
	 */
	const size_t kSHA1OutputBytes = 160 / 8;
	unsigned char sha1[kSHA1OutputBytes];
	if (!SHA1String((unsigned char*)encodedMessage, charCount, sha1))
	{
		error("Failed to SHA1 encode response.");
		return;
	}
	
	// Encode the whole thing in Base64
	base64Encode(sha1, kSHA1OutputBytes, encodedMessage);
	
	char response[256];
	
	sprintf(response,
					"HTTP/1.1 101 Switching Protocols\r\n"
					"Upgrade: websocket\r\n"
					"Connection: Upgrade\r\n"
					"Sec-WebSocket-Accept: %s\r\n\r\n",
					encodedMessage);
	
	size_t responseLength = strlen(response);
	
	if (send(_fileDescriptor, response, responseLength + 1, 0) == -1)
	{
		error("send().");
	}
}

