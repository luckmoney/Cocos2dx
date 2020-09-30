#include "GeometrySubPass.h"
#include "Framework/Render/OpenglRender.h"

namespace Cocos {
	void GeometrySubPass::Draw(Frame& frame) {
		
		auto pipelineState = g_PipelineManager->GetPipelineState("Basic");
		g_RenderSystem->SetPipelineState(&pipelineState,frame);

		glm::mat4 view = glm::lookAt(glm::vec3(0,0.5,1.0f),glm::vec3(0,1.0,0.0f),glm::vec3(0,1,0));
		glm::mat4 proj = glm::perspective(glm::radians(30.0f), (float)4 / 3, 0.1f, 100.f);
		 
		view = glm::mat4(1.0f);
		view = glm::scale(view, glm::vec3(0.1,0.1,0.1));
		view = glm::translate(view, glm::vec3(0, -6.0, 0));

		g_RenderSystem->setShaderParameter("view", view);

		g_RenderSystem->DrawBatch(frame);
	}
}