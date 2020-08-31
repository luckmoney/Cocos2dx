#pragma once 

#include <string>
namespace Cocos {

	enum DEPTH_TEST_MODE
	{
		NONE,LARGE,LARGE_EQUAL,EQUAL,LESS_EQUAL,LESS,NOT_EQUAL,NEVER,ALWAYS
	};

	enum CULL_FACE_MODE {
		NONE,FRONT,BACK
	};

	struct PipelineState {
		virtual ~PipelineState() = default;

		std::string pipelineStateName;

		std::string vertexShaderName;
		std::string pixelShaderName;

		DEPTH_TEST_MODE depthTestMode{DEPTH_TEST_MODE::ALWAYS};
		CULL_FACE_MODE cullFaceMode{ CULL_FACE_MODE::BACK };

		uint32_t shaderProgram = 0;
	
	};
}