#include "GeometrySubPass.h"
#include "Framework/Render/OpenglRender.h"

namespace Cocos {
	void GeometrySubPass::Draw(Frame& frame) {
		
		auto pipelineState = g_PipelineManager->GetPipelineState("Basic");
		g_RenderSystem->SetPipelineState(&pipelineState,frame);

		auto camNode = g_SceneSystem->GetFirstCameraNode();
		auto camObj = g_SceneSystem->GetCamera(camNode->GetSceneObjectRes());

		glm::mat4 view = camObj->GetView();
		glm::mat4 proj = glm::perspective(glm::radians(30.0f), (float)4 / 3, 0.1f, 100.f);
		 
		view = glm::scale(view, glm::vec3(0.1, 0.1, 0.1));
		view = glm::translate(view, glm::vec3(0, -6.0, 0));

		g_RenderSystem->setShaderParameter("view", view);

		g_RenderSystem->DrawBatch(frame);
	}
}