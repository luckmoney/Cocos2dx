#include "modelLoading/ModelLoading.h"


void ModelLoading::Init()
{
	m_shader = new Shader("../OpenGlLearn/src/modelLoading/model_loading.vs", "../OpenGlLearn/src/modelLoading/model_loading.fs");
	m_model = new Model("../OpenGlLearn/res/objects/nanosuit/nanosuit.obj");
}

void ModelLoading::Render(Camera* camera)
{
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->use();

	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	m_shader->setMat4("projection", projection);
	m_shader->setMat4("view", view);

	// render the loaded model
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
	m_shader->setMat4("model", model);
	m_model->Draw(*m_shader);

}