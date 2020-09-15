#pragma once 
#include "Framework/Cocos2dx.h"
namespace Cocos {

	enum class DEPTH_TEST_MODE
	{
		NONE,LARGE,LARGE_EQUAL,EQUAL,LESS_EQUAL,LESS,NOT_EQUAL,NEVER,ALWAYS
	};

	enum class CULL_FACE_MODE {
		NONE,FRONT,BACK
	};

	struct PipelineState {
		virtual ~PipelineState() = default;

		std::string pipelineStateName;

		std::string vertexShaderName;
		std::string pixelShaderName;
		bool bDepthWrite{ true };

		DEPTH_TEST_MODE depthTestMode{DEPTH_TEST_MODE::ALWAYS};
		CULL_FACE_MODE cullFaceMode{ CULL_FACE_MODE::BACK };

		uint32_t shaderProgram = 0;
	
	};


	class PipelineStateManager :public IRuntimeModule {
	public:
		int Initialize();
		void Tick() {};
		void Finalize();

		PipelineState& GetPipelineState(const std::string&);

	private: 
		bool registerPipelineState(PipelineState&);

		void checkCompileErrors(unsigned int shader, std::string type);

	private:
		std::unordered_map<std::string, PipelineState> m_pipeline_map;

	};

	extern PipelineStateManager* g_PipelineManager;
}