#pragma once

#include <string>
#include <vector>

namespace Cocos {

	class SceneNode;
	class SceneMesh;

	enum class SceneObjectType {
		Geometry, Light, Camera
	};


	class SceneObject {


	public:
		static SceneObject* create(SceneObjectType type = SceneObjectType::Geometry);

		SceneObject(SceneObjectType type= SceneObjectType::Geometry):m_Type(type) {

		}

		SceneObjectType GetType() { return m_Type; }

		void SetKey(const std::string key) { m_key = key; }

		void AttendNode(SceneNode* node) {
			m_Node = node;
		}

		void AddMesh(SceneMesh);


		std::vector<SceneMesh>& GetMeshArrary() {
			return m_MeshVec;
		}
	private:
		SceneNode* m_Node;
		std::string m_key;

		SceneObjectType m_Type;
		std::vector<SceneMesh> m_MeshVec;

	};
}

