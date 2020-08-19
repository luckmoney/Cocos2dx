#include "Framework/Windows.h"

namespace Cocos {

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

	}


	void processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);


	}


	static void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}



	int Windows::Initialize() {
		m_deltaFrame = 0.0f;
		m_lastFrame = 0.0f;
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		m_window = glfwCreateWindow(WINDOWSWIDTH, WINDOWSHEIGHT, "Cocos2d", NULL, NULL);
		if (m_window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(m_window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}
		glfwSetCursorPosCallback(m_window, mouse_callback);
		glfwSetScrollCallback(m_window, scroll_callback);
		glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);


		return 0;
	}

	void Windows::Tick() {

	}

	void Windows::Finalize() {

	}

	bool Windows::IsClose() {
		return glfwWindowShouldClose(m_window);
	}

	void Windows::SwapBuffers() {
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	float Windows::GetDelta() {
		float currentFrame = glfwGetTime();
		m_deltaFrame = currentFrame - m_lastFrame;
		m_lastFrame = currentFrame;
		return m_deltaFrame;
	}
}