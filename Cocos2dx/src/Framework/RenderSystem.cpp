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
		CalculateCameraMatrix();
		CalculateLights();
	}

	void RenderSystem::CalculateCameraMatrix() {
		auto pCameraNode = g_SceneSystem->GetFirstCameraNode();
		DrawFrameContext& frameContext = m_Frames[m_nFrameIndex].frameContext;
		if (pCameraNode)
		{
			frameContext.camPos = Vec4(pCameraNode->getPosition(),1.0);
		}

	}

	void RenderSystem::CalculateLights() {
		auto& frameContext = m_Frames[m_nFrameIndex].frameContext;
		auto& light_info = m_Frames[m_nFrameIndex].lightInfo;

		frameContext.numLights = 0;

		auto light_map = g_SceneSystem->GetLightNodes();

		for (const auto mLight : light_map)
		{
			Light& light = light_info.lights[frameContext.numLights];
			auto pLightNode = mLight;

			light.lightPosition = Vector4f(pLightNode->getPosition(), 1.0f);
			light.lightDirection = Vector4f(0, 0, 0, 0.0f);
			auto key = pLightNode->GetSceneObjectRes();
			auto pLight = g_SceneSystem->GetLight(key);
			light.lightColor = pLight->GetColor().Value;
			light.lightIntensity = pLight->GetIntensity();
			light.lightCastShadow = pLight->GetIfCastShadow();
			const AttenCurve& atten_curve = pLight->GetDistanceAttenuations();
			light.lightDistAttenCurveType = atten_curve.type;
			memcpy(light.lightDistAttenCurveParams, &atten_curve.u, sizeof(atten_curve.u));

			++frameContext.numLights;
		}
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
