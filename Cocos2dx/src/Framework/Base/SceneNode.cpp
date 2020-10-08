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


	std::ostream& operator<<(std::ostream&out, SceneNode* object) {
		Vec3 pos = object->getPosition();
		out << "object " << pos.x << "\t" << pos.y << "\t" << pos.z << std::endl;
		return out;
	}
}

