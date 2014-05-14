//
//  webSocketSession.h
//  SpaceJunk
//
//  Created by ixtli on 5/11/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__webSocketSession__
#define __SpaceJunk__webSocketSession__

#include "webSocketMessage.h"

#include "httpRequestHeaders.h"

class WebSocketSession
{
public:
	
	WebSocketSession(int fd);
	~WebSocketSession();
	
	bool init();
	void newData();
	
	bool open() const { return _open; };
	
private:
	
	bool _open;
	int _fileDescriptor;
	WebSocketMessage _message;
	HTTPRequestHeaders _handshakeHeaders;
	
	void sendHandshake();
	
};

#endif /* defined(__SpaceJunk__webSocketSession__) */
