#include "Framework/Base/SceneObjectCamera.h"
#include "Framework/Base/SceneMesh.h"

namespace Cocos {
	SceneObjectCamera::SceneObjectCamera()
		:SceneObject()
		,Yaw(-90.f)
		,Pitch(0.0)
		,MouseSensitivity(SENSITIVITY)
		,Front(Vec3(0,0,-1.0))
	
	{

	}

	Mat4 SceneObjectCamera::GetProjView() {
		glm::mat4 proj = glm::perspective(glm::radians(30.0f), (float)WINDOWSWIDTH / WINDOWSHEIGHT, 0.1f, 100.f);
		return proj * GetView();
	}

	Mat4 SceneObjectCamera::GetView() {
		auto node = this->GetNode();
		Vec3 pos = node->getPosition();
		return glm::lookAt(pos,pos + Front,
			Vec3(0,1,0));
	}

	void SceneObjectCamera::ProcessMouseMovement(float& xoffset, float& yoffset)
	{
		xoffset *= SENSITIVITY;
		yoffset *= SENSITIVITY;

		Yaw += xoffset;
		Pitch += yoffset;

		if (Pitch > 89.0f)
		{
			Pitch = 89.0f;
		}
		if (Pitch < -89.0f)
		{
			Pitch = -89.0f;
		}
		updateCameraVectors();
	}

	void SceneObjectCamera::updateCameraVectors() {
		Vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

		Front = glm::normalize(front);


	}
}