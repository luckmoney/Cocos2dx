#include "Framework/SceneSystem.h"

namespace Cocos {
	SceneSystem* g_SceneSystem = new SceneSystem();

	int SceneSystem::Initialize() {
		SkyBox = std::make_shared<SceneObjectSkyBox>();
		SkyBox->SetName("../Cocos2dx/res/skybox/skybox","jpg");

		m_object = SceneObject::create();

		geometry_cnt = 0;
		light_cnt = 0;
		camera_cnt = 0;

		return 0;
	}

	void SceneSystem::Tick() {
	}

	void SceneSystem::Finalize() {
		SAFEDELETE m_object;
	}


	std::shared_ptr<SceneCameraNode> SceneSystem::GetFirstCameraNode()
	{
		return m_CameraVec.empty() ? nullptr : (*m_CameraVec.begin());
	}


	SceneObject* SceneSystem::GetSceneObject() {
		return m_object;
	}


	void SceneSystem::AddObject(std::shared_ptr<SceneObject>  obj) {
	    std::shared_ptr<SceneNode> node = std::make_shared<SceneNode>();
		std::string key = "geometry_" + geometry_cnt++;
		node->AddSceneObjectRef(key);
		obj->AttendNode(node);
		obj->SetKey(key);
		m_geometroies.insert(std::make_pair(key,obj));
	
		m_NodeVec.push_back(std::move(node));
	}

	std::shared_ptr<SceneObjectLight> SceneSystem::AddLight(std::shared_ptr<SceneObjectLight>m_light, LightType type) {
		std::shared_ptr<SceneLightNode> obj = std::make_shared<SceneLightNode>();
		std::string key = "light_" + light_cnt++;
		obj->AddSceneObjectRef(key);
		m_light->SetKey(key);
		m_light->AttendNode(obj);
		m_Lights.insert(std::make_pair(key, m_light));
		m_LightNodeVec.push_back(std::move(obj));
		return m_light;
	}


	std::shared_ptr<SceneObjectCamera> SceneSystem::AddCamera(std::shared_ptr<SceneObjectCamera>m_Camera) {
		std::shared_ptr<SceneCameraNode> node = std::make_shared<SceneCameraNode>();
		std::string key = "camera_" + camera_cnt++;
		node->AddSceneObjectRef(key);
		m_Camera->SetKey(key);
		m_Camera->AttendNode(node);
		m_Cameras.insert(std::make_pair(key, m_Camera));
		m_CameraVec.push_back(std::move(node));
		return m_Camera;
	}

	std::shared_ptr<SceneObjectLight> SceneSystem::GetLight(const std::string& key) {
		auto iter = m_Lights.find(key);
		if (iter != m_Lights.end())
		{
			return (*iter).second;
		}
		return nullptr;
	};

	std::shared_ptr<SceneObjectCamera> SceneSystem::GetCamera(const std::string& key) {
		auto iter = m_Cameras.find(key);
		if (iter != m_Cameras.end())
		{
			return (*iter).second;
		}
		return std::make_shared<SceneObjectCamera>();
	}
}