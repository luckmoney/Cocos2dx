#include "Framework/Application.h"
namespace Cocos {
	int Application::Initialize()
	{

		InputSystem *input = new InputSystem();
		input->Initialize();
		module_vec.push_back(input);

		SceneSystem *scene = new SceneSystem();
		scene->Initialize();
		module_vec.push_back(scene);

		RenderSystem *render = new RenderSystem();
		render->Initialize();
		module_vec.push_back(render);


		m_bQuit = false;
		return 0;
	}

	void Application::Finalize() {
		auto iter = module_vec.begin();
		while (iter != module_vec.end()) {
			(*iter)->Finalize();
			SAFEDELETE *iter;
			++iter;
		}
	}

	void Application::Tick() {
		auto iter = module_vec.begin();
		while (iter != module_vec.end())
		{
			(*iter)->Tick();
			++iter;
		}
	}

	bool Application::IsQuit() {
		return m_bQuit;
	}

}
