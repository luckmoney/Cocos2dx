#include "SkyboxSubPass.h"
#include "Framework/Render/OpenglRender.h"

namespace Cocos {
	void SkyboxSubPass::Draw(Frame& frame) {

		auto pipelineState = g_PipelineManager->GetPipelineState("SkyBox");
		g_RenderSystem->SetPipelineState(&pipelineState,frame);

		auto camNode = g_SceneSystem->GetFirstCameraNode();
		auto camObj = g_SceneSystem->GetCamera(camNode->GetSceneObjectRes());

		glm::mat4 view = glm::mat4(glm::mat3(camObj->GetProjView()));


		g_RenderSystem->setShaderParameter("view", view);
		g_RenderSystem->DrawSkyBox();
	}
}