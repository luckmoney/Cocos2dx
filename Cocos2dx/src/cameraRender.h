#pragma once

#ifndef CAMERARENDER_H
#define CAMERARENDER_H

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

#include "camera.h"

class CameraRander {

public:
	CameraRander();

	~CameraRander();

	void processInput(GLFWwindow *window);


	void render(GLFWwindow*);

private:
	unsigned int VBO, VAO;
	//load and create a texture
	unsigned int texture1, texture2;
	Shader* ourShader;

	float deltaTime;
	float lastFrame;

public:
	Camera* camera;

};



#endif

