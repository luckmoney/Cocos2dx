#pragma once

#include "Framework/Base/ParameterValueMap.h"

namespace Cocos {
	class SceneObjectCamera {
	protected:
		float m_fAspect;
		float m_fNearClipDistance;
		float m_fFarClipDistance;

	};

	class SceneObjectOrthogonalCamera : public SceneObjectCamera
	{
	};

	class SceneObjectPerspectiveCamera : public SceneObjectCamera
	{
	protected:
		float m_fFov;
	};
}