#include "GeometrySubPass.h"
#include "Framework/Render/OpenglRender.h"

namespace Cocos {
	void GeometrySubPass::Draw() {
		
		auto pipelineState = g_PipelineManager->GetPipelineState("Basic");
		g_RenderSystem->SetPipelineState(&pipelineState);

		g_RenderSystem->DrawBatch();
	}
}