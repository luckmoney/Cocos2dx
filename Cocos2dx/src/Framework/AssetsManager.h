#pragma once 

#include <string>
#include "Framework/Base/SceneObject.h"

namespace Cocos {

	class AssetsManager {
	public:
		std::string readTextFromFile(const char*);

		std::shared_ptr<SceneObject> loadModel(const char*);
	};
	extern AssetsManager* g_AssetsManager;
}