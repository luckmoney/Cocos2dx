#pragma once

#include <string>


namespace Cocos {

	class SceneObjectTexture {
	private:
		std::string m_Name;
		int m_width, m_height, nrComponents;
		unsigned char * m_data;

	public:
		SceneObjectTexture(){}

		explicit SceneObjectTexture(const std::string& name)
		:m_Name(name){
			TextureFromFile(m_Name.c_str());
		}

		void SetName(const std::string& name) {
			m_Name = name;
			TextureFromFile(m_Name.c_str());
		}

		void TextureFromFile(const char* path);

		std::string GetName() { return m_Name; }

		int GetWidth() { return m_width; }

		int GetHeight() { return m_height; }

		unsigned char * GetTextureImage() { return m_data; }

		int GetComponent() { return nrComponents; }

		void FreeImage();
	};
}