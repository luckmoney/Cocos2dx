#include "GeometrySubPass.h"
#include "Framework/Render/OpenglRender.h"

namespace Cocos {
	void GeometrySubPass::Draw(Frame& frame) {
		
		auto pipelineState = g_PipelineManager->GetPipelineState("Basic");
		g_RenderSystem->SetPipelineState(&pipelineState,frame);

		auto camNode = g_SceneSystem->GetFirstCameraNode();
		auto camObj = g_SceneSystem->GetCamera(camNode->GetSceneObjectRes());
		g_RenderSystem->SetShadowMaps(frame);
		g_RenderSystem->DrawBatch(frame);
	}
}