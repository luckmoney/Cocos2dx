#include "Framework/Application.h"
#include "Cocos2dx.h"
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
		auto obj = g_AssetsManager->loadModel("../Cocos2dx/res/objects/nanosuit/nanosuit.obj");
		auto obj_node = obj->GetNode();
		obj_node->setPosition(Vec3(0,0,-0.5));

		std::shared_ptr<SceneObjectOmniLight> omni_light = std::make_shared<SceneObjectOmniLight>();
		omni_light->SetColor("light",Vector4f(0.0f, 1.0f, 1.0, 1.f));
		g_SceneSystem->AddLight(omni_light, LightType::Omni);
		auto node = omni_light->GetNode();
		node->setPosition(Vec3(1,1,1.0));


		std::shared_ptr<SceneObjectSpotLight> spot_light = std::make_shared<SceneObjectSpotLight>();
		spot_light->SetColor("light", Vector4f(0.0, 0, 1.0, 1.0f));
		g_SceneSystem->AddLight(spot_light, LightType::Spot);
		auto spot_node = spot_light->GetNode();
		spot_node->setPosition(Vec3(1, -1, 1));

		std::shared_ptr<SceneObjectCamera> camera = std::make_shared<SceneObjectCamera>();
		g_SceneSystem->AddCamera(camera);
		auto camera_node = camera->GetNode();
		camera_node->setPosition(Vec3(0, 0, 1.0f));


	}

}
