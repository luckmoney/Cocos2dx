#include "Framework/SceneSystem.h"

namespace Cocos {
	SceneSystem* g_SceneSystem = new SceneSystem();

	int SceneSystem::Initialize() {
		SkyBox = std::make_shared<SceneObjectSkyBox>();
		SkyBox->SetName("../Cocos2dx/res/skybox/skybox","jpg");

		m_object = SceneObject::create();

		geometry_cnt = 0;
		omni_light_cnt = 0;
		spot_light_cnt = 0;
		area_light_cnt = 0;
		infinity_light_cnt = 0;

		return 0;
	}

	void SceneSystem::Tick() {
	}

	void SceneSystem::Finalize() {
		SAFEDELETE m_object;
	}


	SceneObject* SceneSystem::GetSceneObject() {
		return m_object;
	}


	void SceneSystem::AddObject(std::shared_ptr<SceneObject>  obj) {
		SceneNode node;
		std::string key = "geometry_" + geometry_cnt++;
		node.AddGeometry(key);
		obj->AttendNode(&node);
		obj->SetKey(key);
		m_geometroies.insert(std::make_pair(key,obj));
	
		m_NodeVec.push_back(std::move(node));
	}

	void SceneSystem::AddNode(SceneNode& node) {
		m_NodeVec.push_back(std::move(node));
	}


	std::shared_ptr<SceneObjectLight> SceneSystem::AddLight(std::shared_ptr<SceneObjectLight>m_light, LightType type) {
		SceneNode obj;
		std::string key;
		switch (type)
		{
		case Cocos::LightType::Omni:
			key = "omni_" + (omni_light_cnt++);
			m_Lights.insert(std::make_pair(key, m_light));
			obj.AddLight(key);
			break;
		case Cocos::LightType::Spot:
			key = "spot_" + (spot_light_cnt++);
			m_Lights.insert(std::make_pair(key, m_light));
			obj.AddLight(key);
			break;
		case Cocos::LightType::Infinity:
			key = "infinity_" + (infinity_light_cnt++);
			m_Lights.insert(std::make_pair(key, m_light));
			obj.AddLight(key);
			break;
		case Cocos::LightType::Area:
			key = "area_" + (area_light_cnt++);
			m_Lights.insert(std::make_pair(key, m_light));
			obj.AddLight(key);
			break;
		default:
			break;
		}
		m_light->SetKey(key);
		m_light->AttendNode(&obj);
		m_NodeVec.push_back(std::move(obj));
		return m_light;
	}


	std::shared_ptr<SceneObjectCamera> AddCamera() {
		std::shared_ptr<SceneObjectCamera> camera;
		return camera;
	}
}