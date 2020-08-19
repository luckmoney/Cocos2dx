#pragma once
#ifndef _Texture_H_
#define _Texture_H_

#include "glad/glad.h"
#include <iostream>
#include "stb_image.h"


class DevTexture {
public:
	std::string type;
	std::string path;

	DevTexture(const char*);

	void bind(GLuint);

private:
	GLuint texture_id;

};


#endif