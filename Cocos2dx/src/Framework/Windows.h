#pragma once
#include "Framework/Cocos2dx.h"

namespace Cocos {
	class Windows :public IRuntimeModule {
	public:
		int Initialize();
		void Tick();
		void Finalize();
		bool IsClose();
		void SwapBuffers();
		float GetDelta();
	private:
		float m_deltaFrame;
		float m_lastFrame;
		GLFWwindow* m_window;
	};
}