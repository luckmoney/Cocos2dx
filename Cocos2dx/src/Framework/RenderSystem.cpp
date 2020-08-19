#include "Framework/RenderSystem.h"

namespace Cocos {
	int RenderSystem::Initialize() {

		return 0;
	}

	void RenderSystem::Tick() {
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3, 0.3, 0.3, 1.0);
	}

	void RenderSystem::Finalize() {

	}

}
