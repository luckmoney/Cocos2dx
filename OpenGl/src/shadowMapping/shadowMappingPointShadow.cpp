
#include "shadowMapping/shadowMappingPointShadow.h"


const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

ShadowMappingPoint::~ShadowMappingPoint()
{

}

void ShadowMappingPoint::Init()
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	shader = new Shader("../Cocos2dx/src/shadowMapping/point_shadow.vs",
		"../Cocos2dx/src/shadowMapping/point_shadow.fs");

	simpeDepthShader = new Shader("../Cocos2dx/src/shadowMapping/point_shadow_depth.vs",
		"../Cocos2dx/src/shadowMapping/point_shadow_depth.fs",
		"../Cocos2dx/src/shadowMapping/point_shadow_depth.gs");


	shader->use();
	shader->setInt("diffuseTexture", 0);
	shader->setInt("depthMap", 1);

	lightPos = glm::vec3(0.0f,0.0f,0.0f);


	m_woodTexture = loadTexture("../Cocos2dx/res/wood.png");


	glGenFramebuffers(1, &m_depthMapFBO);
	glGenTextures(1, &m_depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_depthCubemap);

	for (GLuint i = 0; i<6;++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer not complete " << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void ShadowMappingPoint::Render(Camera *camera,bool shadow)
{

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat aspect = (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT;
	GLfloat near_plane = 1.0f;
	GLfloat far_plane = 25.0f;
	glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), aspect, near_plane, far_plane);
	std::vector<glm::mat4> shadowTransforms;
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));



	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	simpeDepthShader->use();
	for (GLuint i = 0 ; i <6;++i)
	{
		simpeDepthShader->setMat4(("shadowMatrices[" + std::to_string(i) + "]").c_str(),
			shadowTransforms[i]);
	}
	simpeDepthShader->setFloat("far_plane", far_plane);
	simpeDepthShader->setVec3("lightPos", lightPos);

	renderScene(simpeDepthShader);

	glBindFramebuffer(GL_FRAMEBUFFER,0);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->use();
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom),
		(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,100.0f);
	glm::mat4 view = camera->GetViewMatrix();
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);

	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", camera->Position);
	shader->setInt("shadows", true);
	shader->setFloat("far_plane", far_plane);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_woodTexture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_depthCubemap);
	renderScene(shader);

}

void ShadowMappingPoint::renderScene(Shader* shader) {

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(10.0));
	shader->setMat4("model", model);
	glDisable(GL_CULL_FACE);
	shader->setInt("reverse_normals", 1);
	renderCube();
	shader->setInt("reverse_normals", 0);
	glEnable(GL_CULL_FACE);

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(4.0f,-3.5f,0.0));
	shader->setMat4("model", model);
	renderCube();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f,3.0f,1.0));
	model = glm::scale(model,glm::vec3(1.5));
	shader->setMat4("model", model);
	renderCube();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 0.0));
	shader->setMat4("model", model);
	renderCube();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 1.5));
	shader->setMat4("model", model);
	renderCube();


	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f, 2.0f, -3.0));
	model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	shader->setMat4("model", model);
	renderCube();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.5f,2.0f,-3.0f));
	model = glm::rotate(model, 60.0f, glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model,glm::vec3(1.5));
	shader->setMat4("model", model);
	renderCube();

}




