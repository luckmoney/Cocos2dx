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

	struct Frame:global_textures {
		std::vector<DrawBatchContext> m_batchContext;
		LightInfo lightInfo;
	};
}

