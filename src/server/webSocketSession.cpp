//
//  webSocketSession.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/11/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "webSocketSession.h"

WebSocketSession::WebSocketSession(int fd) :

_fileDescriptor(fd),
_message(fd),
_open(false)

{}

WebSocketSession::~WebSocketSession()
{
	
}

bool WebSocketSession::init()
{
	_open = _message.init();
	
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

