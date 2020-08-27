#include "Framework/Application.h"
namespace Cocos {
	int Application::Initialize()
	{

		InputSystem *input = new InputSystem();
		input->Initialize();
		m_InputSystem = input;

		SceneSystem *scene = new SceneSystem();
		scene->Initialize();
		m_SceneSystem = scene;

		RenderSystem *render = new RenderSystem();
		render->Initialize();
		m_RenderSystem = render;

		m_window = new Windows();
		m_window->Initialize();
		m_bQuit = false;

		InitScene();
		return 0;
	}

	void Application::Finalize() {
		m_RenderSystem->Finalize();
		SAFEDELETE(m_RenderSystem);
		m_SceneSystem->Finalize();
		SAFEDELETE(m_SceneSystem);
		m_InputSystem->Finalize();
		SAFEDELETE(m_InputSystem);
		m_window->Finalize();
		SAFEDELETE(m_window);

	}

	void Application::Tick() {
		m_InputSystem->Tick();
		m_SceneSystem->Tick();
		m_RenderSystem->Tick();
		m_window->Tick();
	}

	bool Application::IsQuit() {
		return m_bQuit;
	}

	void Application::Run() {
		while (!m_window->IsClose())
		{
			float delta = m_window->GetDelta();
			this->Tick();
			m_window->SwapBuffers();
		}
		this->Finalize();
	}


	void Application::InitScene() {
		auto obj = m_SceneSystem->GetSceneObject();


	}
}
