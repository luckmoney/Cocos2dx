#pragma once 

#include <glm/glm.hpp>
#define  SAFEDELETE delete
#define  WINDOWSWIDTH 800
#define  WINDOWSHEIGHT 600

#define MAX_LIGHTS 100

typedef glm::vec3 Vec3;
typedef glm::vec4 Vector4f;
typedef glm::vec2 Vector2f;


namespace Cocos {
	enum class LightType { Omni = 0, Spot = 1, Infinity = 2, Area = 3 };
}

struct Light {
	Cocos::LightType lightType;
	float lightIntensity;
	Vector4f lightPosition;
	Vector4f lightColor;
};