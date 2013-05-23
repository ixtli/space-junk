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
	
	typedef enum
	{
		SOLID_QUAD_SHADER,
		NUM_SHADER_TYPES
	} ShaderTypes;
	
	inline static ShaderManager* getInstance() { return &_instance; };
	
	inline static void use(ShaderTypes type)
	{
		if (_currentProgramID == type) return;
		glUseProgram(_instance._shaders[type].id());
		_currentProgramID = type;
	};
	
	void setMVPMatrix(const matrix4f& mvp);
	bool init();
	
private:
	
	static const Shader::ShaderMetadata _shaderMetadata[NUM_SHADER_TYPES];
	
	Shader _shaders[NUM_SHADER_TYPES];
	
	ShaderManager();
	~ShaderManager();
	
	static ShaderManager _instance;
	static ShaderTypes _currentProgramID;
	
};

#endif /* defined(__SpaceJunk__shaderManager__) */
