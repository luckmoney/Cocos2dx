#include "Framework/RenderSystem.h"

namespace Cocos {

	int RenderSystem::Initialize() {

		Frame frame;
		m_Frames.push_back(std::move(frame));

		ShadowPass *shadow = new ShadowPass();
		m_passes.push_back(shadow);

		ForwardPass *forward = new ForwardPass();
		forward->Init();
		m_passes.push_back(forward);

		BeginScene();

		return 0;
	}

	void RenderSystem::Tick() {
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
