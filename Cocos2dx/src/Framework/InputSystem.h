#pragma once
#include "Framework/Cocos2dx.h"

namespace Cocos {
	class InputSystem :public IRuntimeModule {
	public:
		int  Initialize();
		void Tick();
		void Finalize();
	};

	extern InputSystem* g_InputSystem;
}