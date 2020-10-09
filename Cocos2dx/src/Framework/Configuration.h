#pragma once
#include <iostream>

namespace Cocos {
	struct GfxConfiguration {
		static const int32_t kMaxShadowMapCount{ 8 };
		static const int32_t kMaxGlobalShadowMapCount{ 1 };
		static const int32_t kMaxCubeShadowMapCount{ 2 };

		static const uint32_t kShadowMapWidth = 512;       // normal shadow map
		static const uint32_t kShadowMapHeight = 512;      // normal shadow map
		static const uint32_t kCubeShadowMapWidth = 512;   // cube shadow map
		static const uint32_t kCubeShadowMapHeight = 512;  // cube shadow map
		static const uint32_t kGlobalShadowMapWidth = 2048;  // shadow map for sun light
		static const uint32_t kGlobalShadowMapHeight = 2048;  // shadow map for sun light
	};
}