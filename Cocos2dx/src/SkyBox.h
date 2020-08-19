#pragma once
#ifndef _SkyBox_H_
#define _SkyBox_H_

#include "camera.h"
#include "Texture.h"
#include "TextureCub.h"
#include "Shader.h"

class SkyBox {
public:
	~SkyBox();
	void Init();
	void Render(Camera*);
private:
	unsigned int cubeVAO, cubeVBO;
	unsigned int skyboxVAO, skyboxVBO;
	DevTexture *cubeTexture;
	DevTextureCub *cubemapTexture;

	Shader *shader;
	Shader *skyboxShader;
};

#endif