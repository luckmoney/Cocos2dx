#ifndef  _GShaderHouse_H_
#define  _GShaderHouse_H_

#include "dev_common.h"
#include "Shader.h"
#include "camera.h"


class GShaderHouse {
public:
	~GShaderHouse();

	void Init();
	void Render(Camera*);

private:
	GLuint VBO, VAO;
	Shader *m_shader;
};

#endif
