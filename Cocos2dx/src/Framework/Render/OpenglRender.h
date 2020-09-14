#pragma once

#include "FrameWork/RenderSystem.h"

namespace Cocos {
	class OpenglRender:public RenderSystem {
	public:
		void BeginScene();
		void EndScene();

		void BeginFrame();
		void EndFrame();

		void DrawPoint();
		void DrawLine();
		void DrawTriangle();

		void DrawGeometry();
		void DrawSkyBox();

		void DrawTerrain();

		void SetPipelineState(PipelineState*);

		void DrawBatch();

		void setMat4(const std::string &name, const glm::mat4 &mat) const;

	private:

		void InitGeometries();

		void InitSkyBox();


		uint32_t m_CurrentShader;

		std::vector<GLuint> m_buffers;
	};

}