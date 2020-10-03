#include "Framework/Base/SceneNode.h"
#include  <ostream>

namespace Cocos {
	SceneNode* SceneNode::create() {
		SceneNode* node = new SceneNode();
		return node;
	}

	void SceneNode::setPosition(Vec3 pos)
	{
		m_position = pos;
	}

	void SceneNode::addChild(SceneNode* node) {
		m_NodeVec.push_back(node);
	}

	void SceneNode::AddLight(std::string& lightIdx) {
		m_lightVec.push_back(lightIdx);
	}

	void SceneNode::AddGeometry(std::string& geometryIdx) {
		m_GeometryVec.push_back(geometryIdx);
	}

	void SceneNode::AddCamera(std::string& cameraIdx) {
		m_CameraVec.push_back(cameraIdx);
	}


	std::ostream& operator<<(std::ostream&out, SceneNode* object) {
		Vec3 pos = object->getPosition();
		out << "object " << pos.x << "\t" << pos.y << "\t" << pos.z << std::endl;
		return out;
	}
}

