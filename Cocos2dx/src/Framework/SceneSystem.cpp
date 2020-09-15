#include "Framework/SceneSystem.h"

namespace Cocos {
	SceneSystem* g_SceneSystem = new SceneSystem();

	int SceneSystem::Initialize() {
		SkyBox = std::make_shared<SceneObjectSkyBox>();
		SkyBox->SetName("../Cocos2dx/res/skybox/skybox","jpg");

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

	void SceneSystem::AddObject(SceneObject& obj) {
		m_geoVec.push_back(std::move(obj));
	}
}