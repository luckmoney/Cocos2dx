#include "SkyboxSubPass.h"
#include "Framework/Render/OpenglRender.h"

namespace Cocos {
	void SkyboxSubPass::Draw(Frame& frame) {

		auto pipelineState = g_PipelineManager->GetPipelineState("SkyBox");
		g_RenderSystem->SetPipelineState(&pipelineState,frame);

		auto camNode = g_SceneSystem->GetFirstCameraNode();
		auto camObj = g_SceneSystem->GetCamera(camNode->GetSceneObjectRes());

		glm::mat4 view = camObj->GetView();
		g_RenderSystem->setShaderParameter("view", Mat4(1.0f));
		g_RenderSystem->DrawSkyBox();
	}
}