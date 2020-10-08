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

		void AddSceneObjectRef(std::string& key) {
			m_keySceneObject = key;
		}

		const std::string& GetSceneObjectRes() {
			return m_keySceneObject;
		}

	private:
		Vec3 m_position;
		std::string m_keySceneObject;
	};


	class SceneLightNode :public SceneNode {

	};

	class SceneCameraNode :public SceneNode {

	};
} 