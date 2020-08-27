#include "Pass.h"

namespace Cocos {
	Pass::~Pass() {
		auto iter = m_subpasses.begin();
		while (iter != m_subpasses.end())
		{
			delete *iter;
		}
	}
}