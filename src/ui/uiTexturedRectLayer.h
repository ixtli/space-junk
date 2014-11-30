//
//  uiTexturedRectLayer.h
//  SpaceJunk
//
//  Created by ixtli on 11/26/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiTexturedRectLayer__
#define __SpaceJunk__uiTexturedRectLayer__

#include "rectLayer.h"
#include "uiLayer.h"
#include "uiTexturedRectElement.h"
#include "shaderManager.h"

#include "textureManager.h"

class UITexturedRectLayer : public UILayer
{
public:
	
	UITexturedRectLayer();
	virtual ~UITexturedRectLayer();
	
	virtual bool init(uint32_t initialCount);
	virtual void depth(uint32_t d) { _depth = d; };
	virtual void update(sj_time_t dt);
	
	void randomRect();
	
	UITexturedRectElement* newElement();
	void removeElement(UITexturedRectElement* e);

	virtual void draw()
	{
		if (!_layer.used()) return;
		
		ShaderManager::use(kShader);
		
		if (TextureManager::bind(&_texture))
		{
			// Texture unit has changed, inform the shader
			GLint _unitLoc = ShaderManager::getUniformLocation("sampler");
			glUniform1i(_unitLoc, _texture.textureUnit());
		}
		
		_layer.draw();
	};

	
private:
	
	RectLayer<UITexturedRectElement, TextureVertex> _layer;
	
	const ShaderFormat kShader = TEXTURED_QUAD_SHADER;
	
	Texture _texture;
	
};

#endif /* defined(__SpaceJunk__uiTexturedRectLayer__) */
