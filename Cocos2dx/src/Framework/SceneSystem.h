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


		std::shared_ptr<SceneCameraNode> GetFirstCameraNode();


		std::unordered_map<std::string, std::shared_ptr<SceneObject> >& GetGeometries() {
			return m_geometroies;
		}

		std::shared_ptr<SceneObjectLight> GetLight(const std::string&);

		std::shared_ptr<SceneObjectCamera> GetCamera(const std::string&);

		std::vector<std::shared_ptr<SceneLightNode> > GetLightNodes() { return m_LightNodeVec; }


		void AddObject(std::shared_ptr<SceneObject>); 


		std::shared_ptr<SceneObjectLight> AddLight(std::shared_ptr<SceneObjectLight>,LightType);

		std::shared_ptr<SceneObjectCamera> AddCamera(std::shared_ptr<SceneObjectCamera>);



		std::unordered_map<std::string, std::shared_ptr<SceneObjectLight>> m_Lights;
		std::unordered_map<std::string, std::shared_ptr<SceneObjectCamera>> m_Cameras;

		std::unordered_map<std::string, std::shared_ptr<SceneObjectMaterial>> m_Materials;

		std::unordered_map<std::string, std::shared_ptr<SceneObject>>    m_geometroies;

	private:
		SceneObject *m_object;
		
		std::vector<SceneObject> m_geoVec;

		std::vector<std::shared_ptr<SceneNode>> m_NodeVec;
		std::vector<std::shared_ptr<SceneLightNode> > m_LightNodeVec;
		std::vector<std::shared_ptr<SceneCameraNode> > m_CameraVec;

		unsigned int light_cnt;
		uint32_t geometry_cnt;
		uint32_t camera_cnt;

	public:
		std::shared_ptr<SceneObjectSkyBox> SkyBox;
	};

	extern SceneSystem* g_SceneSystem;
}