#pragma  once
#include "Framework/Cocos2dx.h"

namespace Cocos {
	class Cube :public RenderAble {
	public:
		static Cube* create();

		virtual void Render();

	private:

	};
}