#pragma once
#include <stdint.h>
#include <vector>
#include "Framework/Common.h"


namespace Cocos {
	struct PerBatchConstants{};

	struct material_textures {
		int32_t diffuseMap = -1;
		int32_t normalMap = -1;
		int32_t specularMap = -1;
		int32_t metallicMap = -1;
		int32_t roughnessMap = -1;
		int32_t aoMap = -1;
		int32_t heightMap = -1;
	};

	struct DrawBatchContext :PerBatchConstants {
		int32_t batchIndex{ 0 };
		unsigned int vao;
		unsigned int mode;
		unsigned int type;
		unsigned int count;
		material_textures material;
	};


	struct global_textures {
		int32_t brdfLUT = -1;
		int32_t skybox = -1;
		int32_t terrainHeightMap = -1;
	};


	struct LightInfo {
		struct Light lights[MAX_LIGHTS];
	};


	struct PerFrameConstants {
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		Vector4f camPos;
		int32_t numLights;
	};

	struct frame_textures {
		int32_t shadowMap = -1;
		int32_t shadowMapCount = 0;

		int32_t globalShadowMap = -1;
		int32_t globalShadowMapCount = 0;

		int32_t cubeShadowMap = -1;
		int32_t cubeShadowMapCount = 0;
	};


	struct DrawFrameContext:frame_textures,PerFrameConstants{};

	struct Frame:global_textures {
		int32_t frameIndex{ 0 };
		DrawFrameContext frameContext;
		std::vector<DrawBatchContext> m_batchContext;
		LightInfo lightInfo;
	};


	const size_t kSizeLightInfo = ALIGN(
		sizeof(LightInfo), 256);  // CB size is required to be 256-byte aligned.

	const size_t kSizePerFrameConstantBuffer = ALIGN(sizeof(PerFrameConstants), 256);
}

