#pragma once
#include "Framework/Cocos2dx.h"

namespace Cocos {
	class RenderAble;

	class SceneObject {
		friend std::ostream& operator<<(std::ostream&,  SceneObject*);

	public:
		static SceneObject* create();

		void addChild(SceneObject*);

		void update();

		void setPosition(Vec3);

		Vec3 getPosition();

		void AddRenderAble(RenderAble*);


	private:
		std::vector<SceneObject*> object_vec;

		std::vector<RenderAble*> render_vec;

		Vec3 m_position;
		RenderAble *m_renderAble;

	};
}

