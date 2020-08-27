#pragma once
#ifndef LIGHTCASTERENDER_H
#define LIGHTCASTERENDER_H

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "camera.h"


#include "stb_image.h"


class LightCasterRender {
public:
	~LightCasterRender() {
		delete lightingShader;
		delete lampShader;

		glDeleteVertexArrays(1, &cubeVAO);
		glDeleteVertexArrays(1, &lightVAO);
		glDeleteBuffers(1, &VBO);
	};

	void Init(Camera *cam) {

		glm::vec3 cubes[]= {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		cubePositions = cubes;

		float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};



		glEnable(GL_DEPTH_TEST);

		camera = cam;

		lightPos = glm::vec3(1.2f, 0.0f, 2.0f);


		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(cubeVAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);


		glGenVertexArrays(1, &lightVAO);
		glBindVertexArray(lightVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		diffuseMap = loadTexture("res/container2.png");
		specularMap = loadTexture("res/container2_specular.png");

		initDirection();
		//initPoint();
		//initSpot();
	};

	//direction rendering
	void initDirection() {

		lampShader = new Shader("shader/lamp.vsh", "shader/lamp.fsh");
		lightingShader = new Shader("shader/lightmap.vsh", "shader/lightmap.fsh");

		lightingShader->use();
		lightingShader->setInt("material.diffuse", 0);
		lightingShader->setInt("material.specular", 1);
	};


	//point rendering 
	void initPoint() {
		lampShader = new Shader("shader/lamp.vsh", "shader/lamp.fsh");
		lightingShader = new Shader("shader/light_casters.vsh", "shader/light_casters.fsh");

		lightingShader->use();
		lightingShader->setInt("material.diffuse", 0);
		lightingShader->setInt("material.specular", 1);
	};


	//spot rendering
	void initSpot() {
		lampShader = new Shader("shader/lamp.vsh", "shader/lamp.fsh");
		lightingShader = new Shader("shader/light_casters.vsh", "shader/light_casters_spot.fsh");

		lightingShader->use();
		lightingShader->setInt("material.diffuse", 0);
		lightingShader->setInt("material.specular", 1);
	};


	void render() {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), 800.f / 600.f, 0.1f, 100.f);
		glm::mat4 view = camera->GetViewMatrix();

		//renderDirection(&projection,&view);
		//renderPoint(&projection, &view);
		renderSpot(&projection,&view);

		glm::mat4 model = glm::mat4(1.0f);
		lightingShader->setMat4("model", model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		glBindVertexArray(cubeVAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightingShader->setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		lampShader->use();
		lampShader->setMat4("projection", projection);
		lampShader->setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lampShader->setMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	};

	void renderDirection(glm::mat4 *projection, glm::mat4 *view) {

		lightingShader->use();
		lightingShader->setVec3("light.position", lightPos);
		lightingShader->setVec3("viewPos", camera->Position);

		lightingShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		lightingShader->setVec3("light.diffuse", 1.0f, 0.5f, 0.5f);
		lightingShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		lightingShader->setFloat("material.shininess", 64.0f);

		lightingShader->setMat4("projection", *projection);
		lightingShader->setMat4("view", *view);

	};


	void renderPoint(glm::mat4 *projection, glm::mat4 *view) {
		lightingShader->use();
		lightingShader->setVec3("light.position", lightPos);
		lightingShader->setVec3("viewPos", camera->Position);

		lightingShader->setVec3("light.ambient",0.2f,0.2f,0.2f);
		lightingShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		lightingShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		lightingShader->setFloat("light.constant", 1.0f);
		lightingShader->setFloat("light.linear", 0.09f);
		lightingShader->setFloat("light.quadratic", 0.032f);

		lightingShader->setFloat("material.shininess", 32.0f);
		lightingShader->setMat4("projection", *projection);
		lightingShader->setMat4("view", *view);
	};
	

	void renderSpot(glm::mat4 *projection, glm::mat4 *view) {
		lightingShader->use();
		lightingShader->setVec3("light.position", camera->Position);
		lightingShader->setVec3("light.direction", camera->Front);
		lightingShader->setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader->setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
		lightingShader->setVec3("viewPos", camera->Position);

		lightingShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		lightingShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		lightingShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		lightingShader->setFloat("light.constant", 1.0f);
		lightingShader->setFloat("light.linear", 0.09f);
		lightingShader->setFloat("light.quadratic", 0.032f);

		lightingShader->setFloat("material.shininess", 32.0f);
		lightingShader->setMat4("projection", *projection);
		lightingShader->setMat4("view", *view);
	};

	

	unsigned int loadTexture(char const *path) {
		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		}
		else {
			std::cout << "Texture failed to load at path: " << path << std::endl;
		}
		stbi_image_free(data);


		return textureID;
	}

private:
	unsigned int VBO, cubeVAO;
	unsigned int lightVAO;

	unsigned int diffuseMap, specularMap;

	Camera *camera;

	Shader* lightingShader;
	Shader* lampShader;

	glm::vec3 lightPos;

	float *vertices;
	glm::vec3 *cubePositions;
};

#endif