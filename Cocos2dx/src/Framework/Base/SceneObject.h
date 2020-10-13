#pragma once

#include <string>
#include <vector>

namespace Cocos {

	class SceneNode;
	class SceneMesh;

	enum class SceneObjectType {
		Geometry, LightOmni,LightInfi,LightSpot,LightArea, Camera
	};


	class SceneObject {


	public:
		static SceneObject* create(SceneObjectType type = SceneObjectType::Geometry);

		SceneObject(SceneObjectType type= SceneObjectType::Geometry):m_Type(type) {

		}

		SceneObjectType GetType() { return m_Type; }

		void SetKey(const std::string key) { m_key = key; }

		void AttendNode(std::shared_ptr<SceneNode> node) {
			m_Node = node;
		}

		std::shared_ptr<SceneNode> GetNode()const { return m_Node; }

		void AddMesh(SceneMesh);


		std::vector<SceneMesh>& GetMeshArrary() {
			return m_MeshVec;
		}

		SceneObjectType GetType()const { return m_Type; }

	private:
		std::shared_ptr<SceneNode> m_Node;
		std::string m_key;

		SceneObjectType m_Type;
		std::vector<SceneMesh> m_MeshVec;

	};
}

