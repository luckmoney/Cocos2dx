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

	const float SENSITIVITY = 0.1f;

	class SceneObjectCamera:public SceneObject {
	public:
		SceneObjectCamera();
		Mat4 GetView();
		Mat4 GetProjView();

		void ProcessMouseMovement(float &,float &);
		void updateCameraVectors();

	protected:
		float m_fAspect;
		float m_fNearClipDistance;
		float m_fFarClipDistance;

	private:
		float MouseSensitivity;
		//Euler Angles
		float Yaw;
		float Pitch;

		Vec3 Front;
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