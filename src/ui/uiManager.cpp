//
//  uiManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/21/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "colorRectUILayer.h"

#include "uiLayer.h"

#include "uiManager.h"

UIManager UIManager::_instance;

UIManager::UIManager() :

_layers(NULL),
_layerCount(0),
_maxLayers(0)

{}

UIManager::~UIManager()
{
	if (_layers) delete [] _layers;
}

bool UIManager::init()
{
	log("Initializing.");
	
	
	ColorRectUILayer* layer = new ColorRectUILayer();
	layer->init();
	
	UIManager::getInstance()->addLayer(layer);
	
	return true;
}

void UIManager::draw()
{
	for (size_t i = 0; i < _instance._layerCount; i++)
		_instance._layers[i]->draw();
}

void UIManager::update(time_t time)
{
	for (size_t i = 0; i < _instance._layerCount; i++)
		_instance._layers[i]->update();
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

bool UIManager::growLayerList()
{
	UILayer** newList = new UILayer* [_maxLayers * 2];
	
	if (!newList)
	{
		error("Attempt to expand layer list failed.");
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
