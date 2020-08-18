
#include "shadowMapping/shadowMappingDepth.h"


const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

ShadowMappingDepth::~ShadowMappingDepth()
{

}

void ShadowMappingDepth::Init()
{

	glEnable(GL_DEPTH_TEST);

	m_depthShader = new Shader("../OpenGlLearn/src/shadowMapping/shadow_mapping_depth.vs",
		"../OpenGlLearn/src/shadowMapping/shadow_mapping_depth.fs");

	m_depthQuad = new Shader("../OpenGlLearn/src/shadowMapping/debug_quad.vs",
		"../OpenGlLearn/src/shadowMapping/debug_quad.fs");


	m_woodTexture = loadTexture("../OpenGlLearn/res/wood.png");



	lightPos = glm::vec3(-2.0f, 4.0f, -1.0f);




	glGenFramebuffers(1, &m_depthMapFBO);
	glGenTextures(1, &m_depthMap);
	glBindTexture(GL_TEXTURE_2D, m_depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	m_depthQuad->use();
	m_depthQuad->setInt("depthMap", 0);
}

void ShadowMappingDepth::Render(Camera *camera)
{

	glm::mat4 lightProjection, lightView;
	glm::mat4 lightSpaceMatrix;
	float near_plane = -1.0f, far_plane = 7.5f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;

	m_depthShader->use();
	m_depthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_woodTexture);
	renderScene(m_depthShader);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f,0.1f,0.1f,1.0);
	m_depthQuad->use();
	m_depthQuad->setFloat("near_plane", near_plane);
	m_depthQuad->setFloat("far_plane", far_plane);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_depthMap);
	renderQuad();

}

void ShadowMappingDepth::renderScene(Shader* shader) {

	glm::mat4 model = glm::mat4(1.0f);
	shader->setMat4("model", model);
	renderPlane();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f,1.5f,0.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader->setMat4("model", model);
	renderCube();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
	model = glm::scale(model, glm::vec3(0.5f));
	shader->setMat4("model", model);

	renderCube();
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	model = glm::scale(model, glm::vec3(0.25));
	shader->setMat4("model", model);
	renderCube();


}




