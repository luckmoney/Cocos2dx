#pragma once
#ifndef _FrameBuffer_H_
#define _FrameBuffer_H_

#include "camera.h"
#include "Texture.h"
#include "Shader.h"

#include <iostream>

class FrameBufferDemo {

public:

	~FrameBufferDemo();

	void Init();

	void render(Camera*);

private:
	unsigned int framebuffer;
	unsigned int textureColorbuffer;
	unsigned int rbo;

	unsigned int cubeVAO, cubeVBO;
	unsigned int planeVAO, planeVBO;
	unsigned int quadVAO, quadVBO;

	DevTexture *cubeTexture;
	DevTexture *floorTexture;
	Shader *shader;
	Shader *screenShader;

};


#endif