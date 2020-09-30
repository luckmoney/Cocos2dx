#pragma  once 

#include <vector>
#include "SubPass.h"

namespace Cocos {
	class Frame;
	class Pass {
		public:
			~Pass();
			virtual void Draw(Frame&) = 0;
			std::vector<SubPass*> m_subpasses;
	};
};
