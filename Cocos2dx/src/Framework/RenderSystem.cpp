#include "Framework/RenderSystem.h"

namespace Cocos {

	int RenderSystem::Initialize() {

		m_crtScene = nullptr;

		Frame frame;
		frame.frameIndex = 0;
		m_Frames.push_back(std::move(frame));
		Frame frame1;
		frame1.frameIndex = 1;
		m_Frames.push_back(std::move(frame1));

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

		UpdateConstants();

		auto &frame = m_Frames[m_nFrameIndex];
		BeginFrame(frame);
		auto iter = m_passes.begin();
		while (iter != m_passes.end())
		{
			(*iter)->Draw(frame);
			++iter;
		}
		EndFrame();
	}

	void RenderSystem::UpdateConstants() {
		CalculateLights();
	}

	void RenderSystem::CalculateLights() {
		auto& frameContext = m_Frames[m_nFrameIndex].frameContext;
		auto& light_info = m_Frames[m_nFrameIndex].lightInfo;

		frameContext.numLights = 0;
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
