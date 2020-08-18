#ifndef  _Model_Loading_H_
#define  _Model_Loading_H_

#include "dev_common.h"
#include "Shader.h"
#include "camera.h"
#include "Model.h"

class ModelLoading {
public :
	void Init();

	void Render(Camera*);

private:
	Shader *m_shader;
	Model *m_model;
};

#endif
