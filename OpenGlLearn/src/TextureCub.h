#pragma once
#ifndef _TextureCub_H_
#define _TextureCub_H_

#include "glad/glad.h"
#include <iostream>
#include "stb_image.h"
#include <vector>
#include <string>

class DevTextureCub {

public:
	DevTextureCub(std::vector<std::string> faces);

	void bind(GLuint);
private:
	GLuint texture_id;
};

#endif