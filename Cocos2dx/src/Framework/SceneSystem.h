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


		std::unordered_map<std::string, std::shared_ptr<SceneObject> >& GetGeometries() {
			return m_geometroies;
		}


		void AddObject(std::shared_ptr<SceneObject>); 

		void AddNode(SceneNode&);

		std::shared_ptr<SceneObjectLight> AddLight(std::shared_ptr<SceneObjectLight>,LightType);

		std::shared_ptr<SceneObjectCamera> AddCamera(SceneObjectCamera&);



		std::unordered_map<std::string, std::shared_ptr<SceneObjectLight>> m_Lights;
		std::unordered_map<std::string, std::shared_ptr<SceneObjectCamera>> m_Cameras;

		std::unordered_map<std::string, std::shared_ptr<SceneObjectMaterial>> m_Materials;

		std::unordered_map<std::string, std::shared_ptr<SceneObject>>    m_geometroies;

	private:
		SceneObject *m_object;
		
		std::vector<SceneObject> m_geoVec;

		std::vector<SceneNode> m_NodeVec;

		uint32_t omni_light_cnt;
		uint32_t spot_light_cnt;
		uint32_t infinity_light_cnt;
		uint32_t area_light_cnt;
		uint32_t geometry_cnt;

	public:
		std::shared_ptr<SceneObjectSkyBox> SkyBox;
	};

	extern SceneSystem* g_SceneSystem;
}