//
//  renderer.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__renderer__
#define __SpaceJunk__renderer__

#include "chronoUtil.h"
#include "geometry.h"
#include "glutil.h"

class Renderer
{
public:
	
	static const GLfloat projectionNear;
	static const GLfloat projectionFar;
	
	inline static Renderer* getInstance() { return &_instance; };
	
	bool init();
	void destroy();
	void update(sj_time_t now);
	
	void resize(const Size2I& newBounds);
	void render();
	
#pragma mark -
#pragma mark Getters
	const Size2I& bounds() const { return _bounds; };
	
#pragma mark -
#pragma mark OpenGL Context state manipulation functions
	
	static inline void bindVAO(GLuint vao)
	{
		if (vao == _currentVAO) return;
		
		glBindVertexArray(vao);
		_currentVAO = vao;
	}
	
	static inline void clearBindings()
	{
		bindVAO(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
private:
	
	typedef enum
	{
		UI_MANAGER,
		CUBE_MANANGER,
		NUM_COMPONENTS
	} RenderComponents;
	
	Renderer();
	virtual ~Renderer();
	
	Size2I _bounds;
	GLuint _defaultFBOName;
	sj_time_t _lastUpdate;
	
	// startup helpers
	void resetGL();
	bool initComponents();
	
	// Currently bound GL handles, to avoid too many calls to the GFX card
	static GLuint _currentVAO;
	
	/* Singleton instance */
	static Renderer _instance;
};

#endif /* defined(__SpaceJunk__renderer__) */
