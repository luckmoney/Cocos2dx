#ifndef  _Shadow_Mapping_Base_H_
#define  _Shadow_Mapping_Base_H_

#include "dev_common.h"
#include "Shader.h"
#include "camera.h"
#include "Texture.h"

class ShadowMappingBase {
public:
	~ShadowMappingBase();
	void Init();
	void Render(Camera *);
private:
	void renderScene(Shader*);


	GLuint planeVAO;
	GLuint planeVBO;
	GLuint m_depthMapFBO;
	GLuint m_depthMap;
	glm::vec3 lightPos;

	GLuint m_woodTexture;

	Shader *m_depthShader;
	Shader *m_depthQuad;
	Shader *m_shader;
};

#endif
