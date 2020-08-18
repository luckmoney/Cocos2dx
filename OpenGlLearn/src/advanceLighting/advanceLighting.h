#ifndef _Advance_Lighting_H_
#define _Advance_Lighting_H_

#include "dev_common.h"
#include "Shader.h"
#include "camera.h"
#include "Texture.h"

class AdvanceLight {
public:
	~AdvanceLight();
	void Init();
	void Render(Camera*,bool);

private:
	GLuint planeVAO, planeVBO;
	Shader *m_shader;
	DevTexture *m_texture;
	glm::vec3 lightPos;
};

#endif
