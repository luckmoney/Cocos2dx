#pragma once

#include "Framework/Cocos2dx.h"
namespace Cocos {

	class SceneMesh;

	class SceneObject {
		friend std::ostream& operator<<(std::ostream&, SceneObject*);

	public:
		static SceneObject* create();

		void addChild(SceneObject*);

		void update();

		void setPosition(Vec3);

		void AddMesh(SceneMesh&&);

		std::vector<SceneMesh>& GetMeshArrary() {
			return m_MeshVec;
		}

		Vec3 getPosition();

	private:
		std::vector<SceneObject*> object_vec;
		Vec3 m_position;

		std::vector<SceneMesh> m_MeshVec;
	};
}

