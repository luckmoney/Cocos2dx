#include "InputSystem.h"
#include <iostream>
namespace Cocos {
	InputSystem* g_InputSystem = new InputSystem();

	int	InputSystem::Initialize() {
		firstMouse = true;
		return 0;
	}

	void InputSystem::Tick() {

	}

	void InputSystem::Finalize() {

	}

	void InputSystem::ProcessKeyBoard(InputKeyEnum inputv) {

		auto node = g_SceneSystem->GetFirstCameraNode();
		Vec3 pos = node->getPosition();
		float velocity = 0.01;// * deltaTime;
		switch (inputv)
		{
		case InputKeyEnum::FORWARD:
			node->setPosition(pos + Vec3(0, 0, -1.0)*velocity);
			break;
		case InputKeyEnum::BACKWARD:
			node->setPosition(pos - Vec3(0, 0, -1.0)*velocity);
			break;
		case InputKeyEnum::LEFT:
			node->setPosition(pos - Vec3(1, 0, 0.0)*velocity);
			break;
		case InputKeyEnum::RIGHT:
			node->setPosition(pos + Vec3(1, 0, 0.0)*velocity);
			break;
		default:
			break;
		}
		std::cout << node << std::endl;
	}


	void InputSystem::ProcessMouseMovement(double& x, double& y)
	{
		auto node = g_SceneSystem->GetFirstCameraNode();
		auto camera = g_SceneSystem->GetCamera(node->GetSceneObjectRes());
		if (firstMouse)
		{
			lastX = x;
			lastY = y;
			firstMouse = false;
		}
		float xoffset = x - lastX;
		float yoffset = lastY - y;
		lastX = x;
		lastY = y;
		camera->ProcessMouseMovement(xoffset,yoffset);
	}
}