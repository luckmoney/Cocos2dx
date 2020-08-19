#include "Framework/RenderSystem.h"

namespace Cocos {
	int RenderSystem::Initialize() {

		return 0;
	}

	void RenderSystem::Tick() {
		std::cout << "renderSystem tick" << std::endl;
	}

	void RenderSystem::Finalize() {

	}

}
