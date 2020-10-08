#pragma once

#include "Framework/Base/ParameterValueMap.h"
#include "Framework/Base/SceneObject.h"

namespace Cocos {
	enum class Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	class SceneObjectCamera:public SceneObject {
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