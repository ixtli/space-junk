//
//  uiManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/21/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "hud.h"

#include "uiLayer.h"

#include "uiManager.h"

UIManager UIManager::_instance;

UIManager::UIManager() :

_layers()

{}

/** Destroy all layers and deinit the class */
UIManager::~UIManager()
{
	
}

/**
 Initialize the manager
 @return true if completed succesfully
 */
bool UIManager::init()
{
	info("Initializing.");
	
	return true;
}

/** Render UI using OpenGL */
void UIManager::draw()
{
	size_t size = _instance._layers.size();
	for (size_t i = 0; i < size; i++)
		_instance._layers[i]->draw();
}

/**
 Update the UI based on time since the last tick
 @param dt the fraction of a second since the last update
 */
void UIManager::update(sjtime_t dt)
{
	size_t size = _layers.size();
	for (size_t i = 0; i < size; i++)
		_instance._layers[i]->update(dt);
}

void UIManager::viewDidResize(const Size2I &bounds)
{
	
}

bool UIManager::addLayer(UILayer *layer)
{
	size_t oldSize = _layers.size();
	
	_layers.push(layer);
	
	return (_layers.size() - oldSize);
}

bool UIManager::removeLayer(UILayer * const layer)
{
	return _layers.removeElement(layer);
}

