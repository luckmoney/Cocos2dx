#include "Framework/SceneSystem.h"

namespace Cocos {
	SceneSystem* g_SceneSystem = new SceneSystem();

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

	std::vector<SceneObject>& SceneSystem::GetGeoArrary() {
		return m_geoVec;
	}
}