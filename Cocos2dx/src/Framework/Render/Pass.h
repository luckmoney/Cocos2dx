#pragma  once 

#include <vector>
#include "SubPass.h"

namespace Cocos {
	class Pass {
		public:
			~Pass() {
				auto iter = m_subpasses.begin();
				while (iter != m_subpasses.end())
				{
					delete *iter;
				}
				++iter;
			}
			virtual void Draw() = 0;
			std::vector<SubPass*> m_subpasses;
	};
}
