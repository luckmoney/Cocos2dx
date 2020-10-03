#pragma once

#include "Framework/Base/ParameterValueMap.h"
#include "Framework/Base/SceneObject.h"

namespace Cocos {

	enum class AttenCurveType {
		kNone, kLinear, kSmooth, kInverse, kInverseSquare
	};

	struct AttenCurve {
		AttenCurveType type{ AttenCurveType::kNone };
		union AttenCurveParams {
			struct LinearParam {
				float begin_atten;
				float end_atten;
			} linear_params;

			struct SmoothParam {
				float begin_atten;
				float end_atten;
			} smooth_params;

			struct InverseParam {
				float scale;
				float offset;
				float kl;
				float kc;
			} inverse_params;

			struct InverseSquareParam {
				float scale;
				float offset;
				float kq;
				float kl;
				float kc;
			} inverse_squre_params;
		} u;
		AttenCurve() = default;
	};
	class SceneObjectLight :public SceneObject {
	protected:
		Color m_LightColor;
		float m_fIntensity;
		AttenCurve m_LightDistanceAttenuation;
		bool m_bCastShadows;
		std::string m_strTexture;

	public:
		void SetIfCanShadow(bool shadow) {
			m_bCastShadows = shadow;
		}

		void SetColor(std::string& attrib, Vector4f& color) {
			if (attrib == "light")
			{
				m_LightColor = Color(color);
			}
		}

		void SetParam(std::string& attrib, float param) {
			if (attrib == "intensity")
			{
				m_fIntensity = param;
			}
		}

		void SetTexture(std::string& attrib, std::string& textureName) {
			if (attrib == "projection")
			{
				m_strTexture = textureName;
			}
		}

		void SetDistanceAttenuation(AttenCurve curve) {
			m_LightDistanceAttenuation = curve;
		}

		const AttenCurve& GetDistanceAttenuations() {
			return m_LightDistanceAttenuation;
		}

		const Color& GetColor() { return m_LightColor; }

		float GetIntensity() { return m_fIntensity; }

		bool GetIfCastShadow() { return m_bCastShadows; }

	protected:
		//	friend std::ostream& operator<<(std::ostream& out, const SceneObjectLight& obj);
	};


	class SceneObjectOmniLight :public SceneObjectLight {
	public:
		SceneObjectOmniLight() :
			SceneObjectLight() {};
	};


	class SceneObjectSpotLight :public SceneObjectLight {
	protected:
		AttenCurve m_LightAngleAttenuation;
	public:
		SceneObjectSpotLight() :
			SceneObjectLight() {};

		void SetAngleAttenuation(AttenCurve curve) {
			m_LightAngleAttenuation = curve;
		}

		const AttenCurve& GetAttenuation() {
			return m_LightAngleAttenuation;
		}
	};


	class SceneObjectInfiniteLight :public SceneObjectLight {
	public:
		SceneObjectInfiniteLight() :
			SceneObjectLight() {};
	};

	class SceneObjectAreaLight :public SceneObjectLight {
	protected:
		Vector2f m_LightDimension;
	public:
		SceneObjectAreaLight() :
			SceneObjectLight(), m_LightDimension({ 1.0f,1.0f }) {};

		const Vector2f& GetDimension() const {
			return m_LightDimension;
		}

		void SetDimension(const Vector2f& dimension) {
			m_LightDimension = dimension;
		}

	};
}
