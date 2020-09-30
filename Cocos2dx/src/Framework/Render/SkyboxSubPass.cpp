#include "SkyboxSubPass.h"
#include "Framework/Render/OpenglRender.h"

namespace Cocos {
	void SkyboxSubPass::Draw(Frame& frame) {

		auto pipelineState = g_PipelineManager->GetPipelineState("SkyBox");
		g_RenderSystem->SetPipelineState(&pipelineState,frame);

		g_RenderSystem->DrawSkyBox();
	}
}