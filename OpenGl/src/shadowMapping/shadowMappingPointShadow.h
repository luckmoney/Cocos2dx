#ifndef  _Shadow_Mapping_PointShadow_H_
#define  _Shadow_Mapping_PointShadow_H_

#include "dev_common.h"
#include "Shader.h"
#include "camera.h"
#include "Texture.h"

class ShadowMappingPoint {
public:
	~ShadowMappingPoint();
	void Init();
	void Render(Camera *,bool);
private:
	void renderScene(Shader*);


	GLuint planeVAO;
	GLuint planeVBO;
	GLuint m_depthMapFBO;
	GLuint m_depthCubemap;
	glm::vec3 lightPos;

	GLuint m_woodTexture;

	Shader *shader;
	Shader *simpeDepthShader;
};

#endif
