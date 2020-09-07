#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Framework/Render/OpenglRender.h"


namespace Cocos {
	RenderSystem *g_RenderSystem = static_cast<RenderSystem*>(new OpenglRender);


	void OpenglRender::BeginScene() {
		InitGeometries();
		InitSkyBox();
	}

	void OpenglRender::EndScene() {
		for (auto &buffer_id:m_buffers )
		{
			glDeleteBuffers(1, &buffer_id);
		}
		m_buffers.clear();
	}

	void OpenglRender::BeginFrame() {
		glClearColor(0.3, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenglRender::EndFrame() {

	}

	void OpenglRender::InitGeometries() {


		auto geoVec = g_SceneSystem->GetGeoArrary();
		for (auto &object: geoVec)
		{
			auto object_mesh_vec = object.GetMeshArrary();
			for (auto &mesh : object_mesh_vec)
			{
				GLuint vao;
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);

				uint32_t mode;
				auto m_type = mesh.GetType();
				switch (m_type)
				{
				case Cocos::MeshPrimitiveType::kPrimitiveTypePointList:
					mode = GL_POINT;
					break;
				case Cocos::MeshPrimitiveType::kPrimitiveTypeLineList:
					mode = GL_LINE;
					break;
				case Cocos::MeshPrimitiveType::kPrimitiveTypeTriList:
					mode = GL_TRIANGLES;
					break;
				default:
					break;
				}

				auto vertex_vec = mesh.GetSceneVertexArrary();	
				unsigned int idx = 0;

				for (auto &vertex: vertex_vec)
				{
					GLuint vbo;
					glGenBuffers(1, &vbo);
					glBindBuffer(GL_ARRAY_BUFFER, vbo);
					glBufferData(GL_ARRAY_BUFFER, vertex.GetSize(), vertex.GetData(), GL_STATIC_DRAW);
					glEnableVertexAttribArray(idx);
					m_buffers.push_back(vbo);
					auto type = vertex.GetDataType();
					switch (type)
					{
					case Cocos::VertexType::Float1:
						glVertexAttribPointer(0, 1, GL_FLOAT, false, 0, nullptr);
						break;
					case Cocos::VertexType::Float2:
						glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);
						break;
					case Cocos::VertexType::Float3:
						glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);
						break;
					case Cocos::VertexType::Float4:
						glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, nullptr);
						break;
					default:
						break;
					}
					++idx;
				}

				auto index_vec = mesh.GetSceneIndexArrary();
				for (auto &Index:index_vec)
				{
					GLuint ibo;
					glGenBuffers(1, &ibo);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, Index.GetSize(), Index.GetData(), GL_STATIC_DRAW);

					uint32_t type;
					auto index_type = Index.GetType();
					switch (index_type)
					{
					case IndexType::kIndexDataTypeInt8:
						type = GL_UNSIGNED_BYTE;
						break;
					case IndexType::kIndexDataTypeInt16:
						type = GL_UNSIGNED_SHORT;
						break;
					case IndexType::kIndexDataTypeInt32:
						type = GL_UNSIGNED_INT;
					default:
						break;
					}

					DrawBatchContext dbc;
					dbc.vao = vao;
					dbc.mode = mode;
					dbc.count = Index.GetCount();
					dbc.type = type;

					for (unsigned int i = 0; i < m_Frames.size(); ++i)
					{
						m_Frames[i].m_batchContext.push_back(dbc);
					}
				}

				glBindVertexArray(0);

			}
		}

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
		for (auto &frame:m_Frames)
		{
			for (auto &context:frame.m_batchContext)
			{
				glBindVertexArray(context.vao);
				glDrawElements(context.mode, context.count, context.type, nullptr);
			}
		}
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