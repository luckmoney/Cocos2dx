#include "GeometrySubPass.h"
#include "Framework/Render/OpenglRender.h"

namespace Cocos {
	void GeometrySubPass::Draw(Frame& frame) {
		
		auto pipelineState = g_PipelineManager->GetPipelineState("Basic");
		g_RenderSystem->SetPipelineState(&pipelineState,frame);

		auto camNode = g_SceneSystem->GetFirstCameraNode();
		auto camObj = g_SceneSystem->GetCamera(camNode->GetSceneObjectRes());

		glm::mat4 view = camObj->GetProjView();
		view = glm::scale(view, glm::vec3(0.1, 0.1, 0.1));

		g_RenderSystem->setShaderParameter("view", view);

		g_RenderSystem->DrawBatch(frame);
	}
}