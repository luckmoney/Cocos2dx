#include "Framework/Application.h"
namespace Cocos {
	int Application::Initialize()
	{
		g_InputSystem->Initialize();
		g_SceneSystem->Initialize();
		g_RenderSystem->Initialize();
		g_Window->Initialize();

		g_PipelineManager->Initialize();

		m_bQuit = false;

		InitScene();
		return 0;
	}

	void Application::Finalize() {
		g_RenderSystem->Finalize();
		SAFEDELETE(g_RenderSystem);
		g_SceneSystem->Finalize();
		SAFEDELETE(g_SceneSystem);
		g_InputSystem->Finalize();
		SAFEDELETE(g_InputSystem);
		g_Window->Finalize();
		SAFEDELETE(g_Window);

	}

	void Application::Tick() {
		g_InputSystem->Tick();
		g_SceneSystem->Tick();
		g_RenderSystem->Tick();
		g_Window->Tick();
	}

	bool Application::IsQuit() {
		return m_bQuit;
	}

	void Application::Run() {
		while (!g_Window->IsClose())
		{
			float delta = g_Window->GetDelta();
			this->Tick();
			g_Window->SwapBuffers();
		}
		this->Finalize();
	}



	void AddMesh(float *vertex_data, size_t vsize, uint32_t *index_data, size_t isize) {
		SceneMesh mesh;
		mesh.Type(MeshPrimitiveType::kPrimitiveTypeTriList);

		SceneIndexArrary indexArr(index_data, isize * sizeof(float), IndexType::kIndexDataTypeInt32);
		mesh.AddIndexArrary(std::move(indexArr));

		SceneVertexArrary verArr(vertex_data, vsize * sizeof(float), VertexType::Float3);
		mesh.AddVertexArrary(std::move(verArr));

		SceneObject obj;
		obj.AddMesh(mesh);
		g_SceneSystem->AddObject(obj);
	}


	void Application::InitScene() {

		size_t i_size = 6;
		uint32_t* index_data = new uint32_t[6]{
			0,1,2,
			0,2,3
		};
		size_t size = 12;
		float* vertex_data = new float[size] {
			0, 0, 0,
				0.5, 0, 0,
				0.5, 0.5, 0,
				0, 0.5, 0
		};

		AddMesh(vertex_data, size, index_data, i_size);

		float* vertex_data_1 = new float[size] {
				-0.5, 0.5, 0,
				0, 0.5, 0,
				0, -0.5, 0,
				-0.5, -0.5, 0
		};
		AddMesh(vertex_data_1, size, index_data, i_size);


	}

}
