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

		std::vector<SceneObject>& GetGeoArrary();

	private:
		SceneObject *m_object;
		
		std::vector<SceneObject> m_geoVec;

	};

	extern SceneSystem* g_SceneSystem;
}