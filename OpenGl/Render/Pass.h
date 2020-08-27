#pragma  once 

#include <vector>
#include "SubPass.h"

namespace Cocos {
	class Pass {
		public:
			~Pass();
			virtual void Draw() = 0;
			std::vector<SubPass*> m_subpasses;
	};
};
