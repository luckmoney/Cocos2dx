#pragma once

#include <string>
#include "Framework/Common.h"

namespace Cocos {
	class SceneObjectMaterial {
	protected:
		std::string m_Name;
		Color m_BaseColor;
		Normal m_Normal;
		Color m_Specular;
	};
}