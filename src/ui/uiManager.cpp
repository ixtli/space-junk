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

_layers(NULL),
_layerCount(0),
_maxLayers(0)

{}

/** Destroy all layers and deinit the class */
UIManager::~UIManager()
{
	if (_layers)
	{
		delete [] _layers;
		_layers = NULL;
		_layerCount = 0;
	}
}

/**
 Initialize the manager
 @return true if completed succesfully
 */
bool UIManager::init()
{
	info("Initializing.");
	
	// @TODO: Put this somewhere else
	// Initialize the HUD
	h = new HUD();
	h->init();
	
	return true;
}

/** Render UI using OpenGL */
void UIManager::draw()
{
	for (size_t i = 0; i < _instance._layerCount; i++)
		_instance._layers[i]->draw();
}

/**
 Update the UI based on time since the last tick
 @param dt the fraction of a second since the last update
 */
void UIManager::update(sjtime_t dt)
{
	h->update(dt);
	
	for (size_t i = 0; i < _instance._layerCount; i++)
		_instance._layers[i]->update(dt);
}

void UIManager::viewDidResize(const Size2I &bounds)
{
	
}

bool UIManager::addLayer(UILayer *layer)
{
	if (!layer) return false;
	
	if (_layerCount >= _maxLayers)
		if (!growLayerList())
			return false;
	
	_layers[_layerCount] = layer;
	_layerCount++;
	
	return true;
}

bool UIManager::removeLayer(const UILayer *layer)
{
	if (!layer) return false;
	
	bool found = false;
	
	for (size_t i = 0; i < _layerCount; i++)
	{
		if (found)
		{
			_layers[i - 1] = _layers[i];
		} else if (layer == _layers[i]) {
			found = true;
		}
	}
	
	if (found)
	{
		_layerCount--;
		_layers[_layerCount] = NULL;
	} else {
		warn("Layer not found.");
	}
	
	return found;
}

bool UIManager::growLayerList()
{
	UILayer** newList = new UILayer* [_maxLayers * 2];
	
	if (!newList)
	{
		error("Allocation failed.");
		return false;
	}
	
	for (size_t i = 0; i < _layerCount; i++)
	{
		newList[i] = _layers[i];
	}
	
	_maxLayers *= 2;
	delete [] _layers;
	_layers = newList;
	
	return true;
}
