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

		virtual void SetPipelineState(PipelineState*) {};
		virtual void DrawBatch() {};
		virtual void DrawSkyBox() {};


		virtual bool setShaderParameter(const char* name, const glm::mat4 &mat)= 0;

	protected:
		std::vector<Pass*> m_passes;
		std::vector<Frame> m_Frames;
		
		SceneSystem *m_crtScene;

		constexpr static float skyboxVertices[]{
			1.0f,  1.0f,  1.0f,   // 0
			-1.0f, 1.0f,  1.0f,   // 1
			1.0f,  -1.0f, 1.0f,   // 2
			1.0f,  1.0f,  -1.0f,  // 3
			-1.0f, 1.0f,  -1.0f,  // 4
			1.0f,  -1.0f, -1.0f,  // 5
			-1.0f, -1.0f, 1.0f,   // 6
			-1.0f, -1.0f, -1.0f   // 7
		};

		constexpr static uint8_t skyboxIndices[]{
			4, 7, 5, 5, 3, 4,
			6, 7, 4, 4, 1, 6,
			5, 2, 0, 0, 3, 5,
			6, 1, 0, 0, 2, 6,
			4, 3, 0, 0, 1, 4,
			7, 6, 5, 5, 6, 2
		};


	};


	extern RenderSystem *g_RenderSystem;
}