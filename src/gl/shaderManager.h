//
//  shaderManager.h
//  SpaceJunk
//
//  Created by ixtli on 5/23/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__shaderManager__
#define __SpaceJunk__shaderManager__

#include "geometry.h"
#include "shader.h"

class ShaderManager
{
public:
	
	inline static ShaderManager* getInstance() { return &_instance; };
	
	inline static void use(ShaderFormat type)
	{
		if (_currentProgramID == type) return;
		glUseProgram(_instance._shaders[type].id());
		_currentProgramID = type;
	};
	
	inline void setMVP(const glm::mat4 &mvp, ShaderFormat s)
	{
		use(s);
		glUniformMatrix4fv(_shaders[s].mvpLoc(), 1, GL_FALSE, glm::value_ptr(mvp));
	}
	
	void applyProjectionMVP(const glm::mat4 &mvp, ProjectionStyle style);
	
	bool init();
	
private:
	
	static const ShaderMetadata _shaderMetadata[NUM_SHADER_TYPES];
	
	Shader _shaders[NUM_SHADER_TYPES];
	
	ShaderManager();
	~ShaderManager();
	
	static ShaderManager _instance;
	static ShaderFormat _currentProgramID;
	
};

#endif /* defined(__SpaceJunk__shaderManager__) */
