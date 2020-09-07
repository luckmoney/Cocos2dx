#include "Framework/RenderSystem.h"

namespace Cocos {

	int RenderSystem::Initialize() {

		m_crtScene = nullptr;

		Frame frame;
		m_Frames.push_back(std::move(frame));

		ShadowPass *shadow = new ShadowPass();
		m_passes.push_back(shadow);

		ForwardPass *forward = new ForwardPass();
		forward->Init();
		m_passes.push_back(forward);



		return 0;
	}

	void RenderSystem::Tick() {
		if (m_crtScene != g_SceneSystem)
		{
			BeginScene();
			m_crtScene = g_SceneSystem;
		}

		BeginFrame();
		auto iter = m_passes.begin();
		while (iter != m_passes.end())
		{
			(*iter)->Draw();
			++iter;
		}
		EndFrame();
	}

	void RenderSystem::Finalize() {
		auto iter = m_passes.begin();
		while (iter != m_passes.end())
		{
			delete (*iter);
			++iter;
		}
		EndScene();
	}


	void RenderSystem::BeginScene() {
		
	}


}
