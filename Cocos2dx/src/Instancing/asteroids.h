#ifndef _Asteroids_H_
#define _Asteroids_H_

#include "dev_common.h"
#include "Shader.h"
#include "Model.h"
#include "GLFW/glfw3.h"
#include "camera.h"

class Asteroids {
public:
	void Init();
	void Render(Camera* );
private:
	
	glm::mat4 *modelMatrices;

	Model *planet;
	Model *rock;

	Shader *aster_shader;
	Shader *planet_shader;

};

#endif
