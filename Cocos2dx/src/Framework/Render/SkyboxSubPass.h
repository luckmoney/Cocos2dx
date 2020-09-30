#pragma once

#include "SubPass.h"

namespace Cocos {
	class Frame;
	class SkyboxSubPass:public SubPass {
		virtual void Draw(Frame&);
	};
}