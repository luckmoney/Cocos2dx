#include "Framework/Base/SceneObject.h"
#include "Framework/Base/SceneMesh.h"

namespace Cocos {
	SceneObject* SceneObject::create(SceneObjectType type) {
		return new SceneObject();
	}

	void SceneObject::AddMesh(SceneMesh mesh) {
		m_MeshVec.push_back(std::forward<SceneMesh>(mesh));
	}
} 