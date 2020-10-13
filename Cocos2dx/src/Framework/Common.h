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

	//用了std140内存布局后，这里要注意对齐
	struct Light {
		Mat4 lightViewMatrix;				//64 bytes
		Mat4 lightProjectionMatrix;			//64 bytes
		LightType lightType;				//4 bytes
		float lightIntensity;				//4 bytes
		int lightCastShadow;				//4 bytes
		int lightShadowMapIndex;			//4 bytes
		AttenCurveType lightDistAttenCurveType; //4 bytes
		AttenCurveType lightAngleAttenCurveType; //4 bytes
		Vector2f LightSize;					// 16 bytes
		Vector4f lightPosition;				//16 bytes
		Vector4f lightColor;				//16 bytes
		Vector4f lightDirection;			//16 bytes
		Vector4f lightDistAttenCurveParams[2];    // 32 bytes
	};
}



#define ALIGN(x, a) (((x) + ((a)-1)) & ~((a)-1))