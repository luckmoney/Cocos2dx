#pragma  once
#include "Framework/Cocos2dx.h"

namespace Cocos {
	class RenderSystem :public IRuntimeModule {
	public:
		int Initialize();
		void Tick();
		void Finalize();
	};
}