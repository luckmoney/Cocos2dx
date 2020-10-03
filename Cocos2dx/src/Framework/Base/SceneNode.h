#pragma once

#include <vector>
#include "Framework/Common.h"

class SceneObject;



namespace Cocos {
	class SceneNode {
		friend std::ostream& operator<<(std::ostream&, SceneNode*);
	public:
		static SceneNode* create();

		SceneNode() {}

		void addChild(SceneNode*);

		void setPosition(Vec3);

		Vec3 getPosition() {
			return m_position;
		}

		void AddLight(std::string& lightIdx);

		void AddCamera(std::string& cameraIdx);

		void AddGeometry(std::string& geometryIdx);

	private:

		Vec3 m_position;
		std::vector<SceneNode*> m_NodeVec;
		std::vector<std::string> m_GeometryVec;
		std::vector<std::string> m_lightVec;
		std::vector<std::string> m_CameraVec;
	};
} 