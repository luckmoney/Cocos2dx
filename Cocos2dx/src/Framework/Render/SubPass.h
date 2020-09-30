#pragma  once

#include "Framework/FrameStructure.h"
namespace Cocos {
	class SubPass {
		public:
			virtual	void Draw(Frame&) = 0;
	};
}