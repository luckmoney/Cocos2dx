#include "geometryShader/geometryShaderHouses.h"

GShaderHouse::~GShaderHouse()
{
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
}

void GShaderHouse::Init()
{
	m_shader = new Shader(
		"../Cocos2dx/shader/geometry_shader.vs", 
		"../Cocos2dx/shader/geometry_shader.fs",
		"../Cocos2dx/shader/geometry_shader.gs"
		);

	float points[] = {
	 -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
	  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
	  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
	 -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);

}

void GShaderHouse::Render(Camera* camera)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 4);
}

