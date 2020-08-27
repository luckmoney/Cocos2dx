#include "Framework/RenderSystem.h"

namespace Cocos {
	int RenderSystem::Initialize() {
		ShadowPass *shadow_pass = new  ShadowPass(); 
		m_psses.push_back(shadow_pass);

		ForwardPass *forward_pass = new ForwardPass();
		m_psses.push_back(forward_pass);

		return 0;
	}

	void RenderSystem::Tick() {

		auto iter = m_psses.begin();
		while (iter != m_psses.end())
		{
			(*iter)->Draw();
			++iter;
		}


		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3, 0.3, 0.3, 1.0);
	}

	void RenderSystem::Finalize() {

	}

}
