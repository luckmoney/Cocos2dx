#pragma  once

#include "Pass.h"
namespace Cocos {
	class Frame;
	class ShadowPass: public Pass {
	public:
		virtual void Draw(Frame&);
	};
}
