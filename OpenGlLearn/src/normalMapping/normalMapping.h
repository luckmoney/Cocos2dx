#ifndef _NormalMapping_H_
#define _NormalMapping_H_

#include "dev_common.h"
#include "Shader.h"
#include "Texture.h"
#include "camera.h"

class NormalMapping {
public:
	~NormalMapping();
	void Init();
	void Render(Camera*);
private:
	void renderQuad();

	unsigned int quadVAO;
	unsigned int quadVBO;

	Shader *shader;
	DevTexture *diffuseMap;
	DevTexture *normalMap;

	glm::vec3 lightPos;
};

#endif
