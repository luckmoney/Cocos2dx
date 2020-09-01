#pragma once 

#include <string>

namespace Cocos {


	class AssetsManager {
	public:
		std::string readTextFromFile(const char*);
	};
	extern AssetsManager* g_AssetsManager;
}