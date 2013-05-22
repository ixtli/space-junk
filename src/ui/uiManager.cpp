//
//  uiManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/21/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "uiManager.h"

UIManager UIManager::_instance;

UIManager::UIManager()
{}

UIManager::~UIManager()
{
	
}

bool UIManager::init()
{
	log("Initializing.");
	
	return true;
}