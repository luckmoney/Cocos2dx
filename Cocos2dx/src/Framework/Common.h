#pragma once 

#include <glm/glm.hpp>
#define  SAFEDELETE delete
#define  WINDOWSWIDTH 800
#define  WINDOWSHEIGHT 600

#define MAX_LIGHTS 10

typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::vec4 Vector4f;
typedef glm::vec2 Vector2f;
typedef glm::mat4 Mat4;



namespace Cocos {
	enum class LightType { Omni = 0, Spot = 1, Infinity = 2, Area = 3 };


	enum class AttenCurveType {
		kNone, kLinear, kSmooth, kInverse, kInverseSquare
	};


	struct Light {
		LightType lightType;
		float lightIntensity;
		AttenCurveType lightDistAttenCurveType;
		int lightCastShadow;
		Vector4f lightPosition;
		Vector4f lightColor;
		Vector4f lightDirection;
		Vector4f lightDistAttenCurveParams[2];    // 32 bytes
	};
}



#define ALIGN(x, a) (((x) + ((a)-1)) & ~((a)-1))