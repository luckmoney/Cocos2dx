#include <iostream>
#include "Framework/Application.h"
#include "Framework/Render/OpenglRender.h"


int main()
{
	float vertices[] = {
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	std::cout << sizeof(vertices) << std::endl;


	Cocos::Application application;
	application.Initialize();
	application.Run();

	return 0;
}
