#pragma  once 
#include "SubPass.h"

namespace Cocos {
	class Frame;
	class TerrainSubPass:public SubPass {
		virtual	void Draw(Frame& );
	};
}