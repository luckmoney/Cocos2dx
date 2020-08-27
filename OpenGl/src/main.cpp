#include "Framework/Cocos2dx.h"

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
	Cocos::Application application;
	application.Initialize();

	application.Run();

	return 0;
}
