#pragma  once

#include "Pass.h"

namespace Cocos {
	class Frame;
	class ForwardPass :public Pass {
	public:
		~ForwardPass();
		void Init();
		virtual void Draw(Frame&);
	};
}
