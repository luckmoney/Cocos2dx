#pragma  once

#include "Pass.h"

namespace Cocos {
	class ForwardPass :public Pass {
	public:
		~ForwardPass();
		void Init();
		virtual void Draw();
	};
}
