#pragma once
#include "Framework/Cocos2dx.h"

namespace Cocos {
	enum class InputKeyEnum{FORWARD,BACKWARD,LEFT,RIGHT};

	class InputSystem :public IRuntimeModule {
	public:
		int  Initialize();
		void Tick();
		void Finalize();

		void ProcessKeyBoard(InputKeyEnum);
		void ProcessMouseMovement(double&, double&);

	private:
		bool firstMouse;
		float lastX = WINDOWSWIDTH * 0.5f;
		float lastY = WINDOWSHEIGHT * 0.5f;
	};

	extern InputSystem* g_InputSystem;
}