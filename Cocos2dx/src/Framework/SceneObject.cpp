#include "SceneObject.h"

namespace Cocos {
	SceneObject* SceneObject::create() {
		return new SceneObject();
	}


	void SceneObject::addChild(SceneObject* child) {
		object_vec.push_back(child);
	}


	void SceneObject::update() {
		//std::cout << this << std::endl;
		auto iter = object_vec.begin();
		while (iter != object_vec.end())
		{
			(*iter)->update();
			++iter;
		}

	}

	void SceneObject::setPosition(Vec3 pos)
	{
		m_position = pos;
	}

	Vec3 SceneObject::getPosition() {
		return m_position;
	}

	std::ostream& operator<<(std::ostream&out, SceneObject* object) {
		Vec3 pos = object->getPosition();
		out << "object " << pos.x << "\t"<< pos.y << "\t"<< pos.z << std::endl;
		return out;
	}



} 