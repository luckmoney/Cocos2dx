#pragma once

#include "FrameWork/RenderSystem.h"

namespace Cocos {
	class OpenglRender {
	public:
		void BeginScene();
		void EndScene();

		void DrawPoint();
		void DrawLine();
		void DrawTriangle();

		void DrawGeometry();
		void DrawSkyBox();

		void DrawTerrain();

		void SetPipelineState(PipelineState*);

		void DrawBatch();

	private:
		uint32_t m_CurrentShader;

	};

	extern OpenglRender *g_openglRender;
}