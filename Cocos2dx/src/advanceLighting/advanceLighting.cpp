#include "advanceLighting/advanceLighting.h"


AdvanceLight::~AdvanceLight() {
	delete m_texture;
	delete m_shader;
}

void AdvanceLight::Init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	lightPos = glm::vec3(0.0f,0.0f,0.0f);

	m_texture = new DevTexture("../Cocos2dx/res/wood.png");
	m_shader = new Shader("../Cocos2dx/src/advanceLighting/advanced_lighting.vs",
		"../Cocos2dx/src/advanceLighting/advanced_lighting.fs");
	m_shader->use();
	m_shader->setInt("floorTexture", 0);

	float planeVertices[] = {
		 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

		 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
		 10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
	};
	glGenVertexArrays(1, &planeVAO);
	glBindVertexArray(planeVAO);

	glGenBuffers(1, &planeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindVertexArray(0);
}

void AdvanceLight::Render(Camera* camera,bool blinn)
{
	glClearColor(0.1f,0.1,0.1f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / SCR_HEIGHT,
		0.1f, 100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	m_shader->setMat4("projection", projection);
	m_shader->setMat4("view", view);

	m_shader->setVec3("viewPos", camera->Position);
	m_shader->setVec3("lightPos", lightPos);
	m_shader->setInt("blinn", blinn);

	glBindVertexArray(planeVAO);
	m_texture->bind(GL_TEXTURE0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	std::cout << blinn << std::endl;
}

