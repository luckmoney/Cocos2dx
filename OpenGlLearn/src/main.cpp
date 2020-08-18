#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "camera.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#include "dev_common.h"


#include "normalMapping/normalMapping.h"
//#include "shadowMapping/shadowMappingPointShadow.h"
//#include "shadowMapping/shadowMappingBase.h"
//#include "SkyBox.h"
//#include "geometryShader/geometryShaderHouses.h"
//#include "modelLoading/ModelLoading.h"
//#include "Instancing/asteroids.h"
//#include "advanceLighting/advanceLighting.h"

float lastX = SCR_WIDTH / 2.0f;
float lasY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f,3.0f));

bool blinn = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window,double xpos ,double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lasY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lasY - ypos;
	lastX = xpos;
	lasY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window,double xoffset,double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);


	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		blinn = !blinn;
	}
}


static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main()
{

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	NormalMapping render;
	render.Init();

	//AdvanceLight adLight;
	//adLight.Init();

	//SkyBox sky_box;
	//sky_box.Init();

	//GShaderHouse g_shader;
	//g_shader.Init();


	//ModelLoading Model;
	//Model.Init();

	//Asteroids aster;
	//aster.Init();

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);


		render.Render(&camera);
		//adLight.Render(&camera, blinn);

		//aster.Render(&camera);
		//Model.Render(&camera);
		//g_shader.Render(&camera);
		//sky_box.Render(&camera);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
