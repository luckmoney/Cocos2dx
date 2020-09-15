#pragma once

#include <string>
#include "Framework/Common.h"
#include "Framework/base/ParameterValueMap.h"


namespace Cocos {
	class SceneObjectMaterial {
	protected:
		std::string m_Name;
		Color m_BaseColor;
		Normal m_Normal;
		Color m_Specular;

		Parameter m_Metallic;
		Parameter m_Height;

	public:
		SceneObjectMaterial(const std::string& name):
		m_Name(name)
		{}

		SceneObjectMaterial(std::string&& name) {
			m_Name = std::move(name);
		}

		const std::string& GetName() const { return m_Name; }
		const Color& GetBaseColor() const { return m_BaseColor; }
		const Color& GetSpecularColor() const { return m_Specular; }
		const Normal& GetNormal() const { return m_Normal; }
		const Parameter GetHeight() const { return m_Height; }
	
		void SetName(const std::string&name) { m_Name = name; }
		void SetName(std::string&& name) { m_Name = std::move(name); }

		void SetColor(const std::string& attrib ,const Color& color) {
			if (attrib == "diffuse")
			{
				m_BaseColor = color;
			}
			else if (attrib == "specular") {
				m_Specular = color;
			}
		}

		void SetParam(const std::string& attrib, const float param) {
			if (attrib == "metallic")
			{
				m_Metallic = Parameter(param);
			}
			else if (attrib == "height") {
				m_Height = Parameter(param);
			}
		}

		void SetTexture(const std::string& attrib, const std::string& textureName) {
			if (attrib == "diffuse")
			{
				m_BaseColor = std::make_shared<SceneObjectTexture>(textureName);
			}
			else if (attrib == "specular") {
				m_Specular = std::make_shared<SceneObjectTexture>(textureName);
			}
			else if (attrib == "normal") {
				m_Normal = std::make_shared<SceneObjectTexture>(textureName);
			}
			else if (attrib == "metallic") {
				m_Metallic = std::make_shared<SceneObjectTexture>(textureName);
			}
			else if (attrib == "height") {
				m_Height = std::make_shared<SceneObjectTexture>(textureName);
			}
		}

		void SetTexture(const std::string& attrib,const std::shared_ptr<SceneObjectTexture>& texture) {
			if (attrib == "diffuse")
			{
				m_BaseColor = texture;
			}
			else if (attrib == "specular") {
				m_Specular = texture;
			}
			else if (attrib == "normal") {
				m_Normal = texture;
			}
			else if (attrib == "metallic") {
				m_Metallic = texture;
			}
			else if (attrib == "height") {
				m_Height = texture;
			}
		}

	};
}