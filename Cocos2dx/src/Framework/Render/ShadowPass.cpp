#include "ShadowPass.h"
#include "Framework/Render/OpenglRender.h"s

namespace Cocos {
	void ShadowPass::Draw(Frame& frame) {
		uint32_t shadowmap_index = 0;
		uint32_t global_shadowmap_index = 0;
		uint32_t cube_shadowmap_index = 0;
		
		for (int32_t i = 0;i < frame.frameContext.numLights;i++)
		{
			auto& light = frame.lightInfo.lights[i];
			if (light.lightCastShadow)
			{
				int32_t shadowmap;
				int32_t width, height;

				const char* pipelineStateName;

				switch (light.lightType)
				{
				case LightType::Omni:
					if (cube_shadowmap_index >= GfxConfiguration::kMaxCubeShadowMapCount)
					{
						continue;
					}
					pipelineStateName = "Omni_Light_Shadow_Map";
					shadowmap = frame.frameContext.cubeShadowMap;
					width = GfxConfiguration::kCubeShadowMapWidth;
					height = GfxConfiguration::kCubeShadowMapHeight;
					light.lightShadowMapIndex = cube_shadowmap_index++;
					break;
				case LightType::Spot:
					if (shadowmap_index >= GfxConfiguration::kMaxShadowMapCount)
					{
						continue;
					}
					pipelineStateName = "Spot_Light_Shadow_Map";
					shadowmap = frame.frameContext.shadowMap;
					width = GfxConfiguration::kShadowMapWidth;
					height = GfxConfiguration::kShadowMapHeight;
					light.lightShadowMapIndex = shadowmap_index++;
					break;
				case LightType::Area:
					if (shadowmap_index >= GfxConfiguration::kMaxShadowMapCount)
					{
						continue;
					}
					pipelineStateName = "Area_Light_Shadow_Map";
					shadowmap = frame.frameContext.shadowMap;
					width = GfxConfiguration::kShadowMapWidth;
					height = GfxConfiguration::kShadowMapHeight;
					light.lightShadowMapIndex = shadowmap++;
					break;
				case LightType::Infinity:
					if (global_shadowmap_index >= GfxConfiguration::kMaxShadowMapCount)
					{
						continue;
					}
					pipelineStateName = "Sun_Light_Shadow_Map";
					shadowmap = frame.frameContext.globalShadowMap;
					width = GfxConfiguration::kGlobalShadowMapWidth;
					height = GfxConfiguration::kGlobalShadowMapHeight;
					light.lightShadowMapIndex = global_shadowmap_index++;
					break;
				default:
					assert(0);
				}

				g_RenderSystem->BeginShadowMap(i,shadowmap,width,height,light.lightShadowMapIndex,frame);
				
				auto& pPipelineState = g_PipelineManager->GetPipelineState(pipelineStateName);
				g_RenderSystem->SetPipelineState(&pPipelineState,frame);
				g_RenderSystem->DrawBatch(frame);

				g_RenderSystem->EndShadowMap(shadowmap,light.lightShadowMapIndex);

			}
		}
		frame.frameContext.globalShadowMap = global_shadowmap_index;
		frame.frameContext.cubeShadowMap = cube_shadowmap_index;
		frame.frameContext.shadowMapCount = shadowmap_index;
	}
}