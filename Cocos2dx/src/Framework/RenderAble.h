#pragma once

namespace Cocos {
	class SceneObject;

	class RenderAble {
	public:

		void SetParent(SceneObject*);

		virtual void Render()= 0;

	private:
		SceneObject *m_parent;
	};
}
