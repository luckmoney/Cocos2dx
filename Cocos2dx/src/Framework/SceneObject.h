#pragma once
#include "Cocos2dx.h"

namespace Cocos {

	class SceneObject {
		friend std::ostream& operator<<(std::ostream&,  SceneObject*);

	public:
		static SceneObject* create();

		void addChild(SceneObject*);

		void update();

		void setPosition(Vec3);

		Vec3 getPosition();




	private:
		std::vector<SceneObject*> object_vec;


		Vec3 m_position;


	};
}

