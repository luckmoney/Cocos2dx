#pragma once

#include "Framework/Cocos2dx.h"

namespace Cocos {
	class SceneObject;
	class SceneSystem :public IRuntimeModule {
	public:
		virtual int Initialize();
		virtual void Finalize();
		virtual void Tick();
		SceneObject* GetSceneObject();

	private:
		SceneObject *m_object;
	};
}