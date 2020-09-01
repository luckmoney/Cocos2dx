#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Framework/Render/OpenglRender.h"


namespace Cocos {
	OpenglRender *g_openglRender = new OpenglRender();


	void OpenglRender::BeginScene() {

	}

	void OpenglRender::EndScene() {
		for (auto &buffer_id:m_buffers )
		{
			glDeleteBuffers(1, &buffer_id);
		}
		m_buffers.clear();
	}

	void OpenglRender::BeginFrame() {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenglRender::EndFrame() {

	}

	void OpenglRender::InitGeometries() {

	}

	void OpenglRender::InitSkyBox() {

	}


	void OpenglRender::DrawPoint()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);

		glBindVertexArray(vao);

		GLuint buffer_id;
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

		float arr[3]{0,0,0};
		glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

		glDrawArrays(GL_POINT, 0x00, 1);

		m_buffers.push_back(buffer_id);
	}

	void OpenglRender::DrawLine()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);

		glBindVertexArray(vao);

		GLuint buffer_id;
		m_buffers.push_back(buffer_id);

		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

		float arr[]{ -0.5,0,0,0.5,0,0 };
		glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3, GL_FLOAT, false, 0, nullptr);

		glDrawArrays(GL_LINE, 0x00, 2);
	}

	void OpenglRender::DrawTriangle()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);

		glBindVertexArray(vao);

		GLuint buffer_id;
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		m_buffers.push_back(buffer_id);

		float arr[]{ -0.5,0,0,0.5,0,0,0,0.5,0 };
		glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

		glDrawArrays(GL_TRIANGLES, 0x00, 3);
	}

	void OpenglRender::DrawGeometry() {
		this->DrawPoint();
	}

	void OpenglRender::DrawSkyBox()
	{

	}

	void OpenglRender::DrawTerrain()
	{

	}



	void OpenglRender::DrawBatch()
	{

	}

	void OpenglRender::SetPipelineState(PipelineState* pipelineState)
	{
		m_CurrentShader = pipelineState->shaderProgram;

		glUseProgram(m_CurrentShader);

		switch (pipelineState->depthTestMode)
		{
		case DEPTH_TEST_MODE::NONE:
			glDisable(GL_DEPTH_TEST);
			break;
		case DEPTH_TEST_MODE::LARGE:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_GREATER);
			break;
		case DEPTH_TEST_MODE::LARGE_EQUAL:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_GEQUAL);
			break;
		case DEPTH_TEST_MODE::LESS:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			break;
		case DEPTH_TEST_MODE::LESS_EQUAL:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			break;
		case DEPTH_TEST_MODE::EQUAL:
			glEnable(GL_DEPTH_TEST);
			break;
		case DEPTH_TEST_MODE::NOT_EQUAL:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_NOTEQUAL);
			break;
		case DEPTH_TEST_MODE::NEVER:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_NEVER);
			break;
		case DEPTH_TEST_MODE::ALWAYS:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_ALWAYS);
			break;
		default:
			assert(0);
		}


		switch (pipelineState->cullFaceMode)
		{
		case CULL_FACE_MODE::NONE:
			glDisable(GL_CULL_FACE);
			break;
		case CULL_FACE_MODE::BACK:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			break;
		case CULL_FACE_MODE::FRONT:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			break;
		default:
			assert(0);
		}

	}

}