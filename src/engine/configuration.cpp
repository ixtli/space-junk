//
//  configuration.cpp
//  SpaceJunk
//
//  Created by ixtli on 12/23/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "./configuration.h"

Configuration Configuration::_instance;

Configuration::Configuration() :

_serverPort(8888)

{}

Configuration::~Configuration()
{
	
}
