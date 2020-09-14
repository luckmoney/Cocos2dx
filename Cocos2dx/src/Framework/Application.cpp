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



	void Application::InitScene() {

		//g_AssetsManager->loadModel("../Cocos2dx/res/objects/cube.obj");
		g_AssetsManager->loadModel("../Cocos2dx/res/objects/nanosuit/nanosuit.obj");

	}

}
