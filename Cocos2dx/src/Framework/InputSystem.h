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
	};

	extern InputSystem* g_InputSystem;
}