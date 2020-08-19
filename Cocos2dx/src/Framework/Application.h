#pragma  once


#include "Framework/Cocos2dx.h"

namespace Cocos {
	class Application :public IRuntimeModule {
	public:
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();
		bool IsQuit();

	private:
		bool m_bQuit;
		std::vector<IRuntimeModule*> module_vec;
	};
}