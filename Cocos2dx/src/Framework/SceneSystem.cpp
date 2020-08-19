#include "Framework/SceneSystem.h"

namespace Cocos {
	int SceneSystem::Initialize() {
		m_object = SceneObject::create();
		return 0;
	}

	void SceneSystem::Tick() {
		m_object->update();
	}

	void SceneSystem::Finalize() {
		SAFEDELETE m_object;
	}


	SceneObject* SceneSystem::GetSceneObject() {
		return m_object;
	}

}