#include "SkyboxSubPass.h"
#include "Framework/Render/OpenglRender.h"

namespace Cocos {
	void SkyboxSubPass::Draw() {

		auto pipelineState = g_PipelineManager->GetPipelineState("SkyBox");
		g_RenderSystem->SetPipelineState(&pipelineState);

		g_RenderSystem->DrawSkyBox();
	}
}