#include "InputSystem.h"

namespace Cocos {
	int	InputSystem::Initialize() {
		return 0;
	}

	void InputSystem::Tick() {
		std::cout << "InputSystem Tick" << std::endl;
	}

	void InputSystem::Finalize() {

	}
}