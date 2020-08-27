#pragma once

#ifndef _Dev_Common_H_
#define _Dev_Common_H_

#include "glad/glad.h"
#include <iostream>


#include "stb_image.h"


#define SCR_WIDTH 800
#define SCR_HEIGHT 600

#define SRC_PATH "../Cocos2dx/"

// ---------------------------------------------------
unsigned int loadTexture(char const * path);



void renderPlane();
void renderCube();
void renderQuad();

#endif


