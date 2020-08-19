#pragma  once


#include "Framework/Cocos2dx.h"

namespace Cocos {
	class Windows;
	class Application :public IRuntimeModule {
	public:
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();
		void Run();
		bool IsQuit();

	private:
		bool m_bQuit;
		std::vector<IRuntimeModule*> module_vec;

		Windows *m_window;
	};
}