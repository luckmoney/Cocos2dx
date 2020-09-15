#include "Framework/Base/SceneObjectTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ASSERT(x)
#include "stb_image.h"


namespace Cocos {

	void SceneObjectTexture::TextureFromFile(const char* path) {
		//stbi_set_flip_vertically_on_load(true);

		std::string filename = std::string(path);
		
		m_data = stbi_load(filename.c_str(),&m_width,&m_height,&nrComponents,0);
	}

	void SceneObjectTexture::FreeImage() {
		stbi_image_free(m_data);
	}
}