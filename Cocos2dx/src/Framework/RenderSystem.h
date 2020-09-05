#pragma  once
#include "Framework/Cocos2dx.h"


namespace Cocos {

	class RenderSystem :public IRuntimeModule {
	public:
		int Initialize();
		void Tick();
		void Finalize();

		virtual void BeginScene();
		void EndScene(){}

		virtual void BeginFrame() =0;
		void EndFrame(){}

		void SetPipelineState(PipelineState*) {};
		void DrawBatch() {};
		void DrawSkyBox() {};

	protected:
		std::vector<Pass*> m_passes;
		std::vector<Frame> m_Frames;

	};


	extern RenderSystem *g_RenderSystem;
}