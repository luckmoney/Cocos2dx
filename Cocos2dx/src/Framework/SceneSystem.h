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

		void AddObject(SceneObject&);

		std::unordered_map<std::string, std::shared_ptr<SceneObjectMaterial>> m_Materials;
	private:
		SceneObject *m_object;
		
		std::vector<SceneObject> m_geoVec;

	public:
		std::shared_ptr<SceneObjectSkyBox> SkyBox;
	};

	extern SceneSystem* g_SceneSystem;
}