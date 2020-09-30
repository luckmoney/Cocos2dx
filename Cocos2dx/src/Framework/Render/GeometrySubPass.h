#pragma  once

#include "SubPass.h"

namespace Cocos {
	class Frame;
	class GeometrySubPass :public SubPass {
		void Draw(Frame&);
	};
}
