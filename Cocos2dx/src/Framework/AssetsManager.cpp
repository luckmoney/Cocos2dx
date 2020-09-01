#include "Framework/AssetsManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace Cocos {
	AssetsManager *g_AssetsManager = new AssetsManager();


	std::string AssetsManager::readTextFromFile(const char* path) {
		std::string code;
		
		std::ifstream ifs;
		ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			ifs.open(path);
			std::stringstream stream;
			stream << ifs.rdbuf();
			code = stream.str();
			ifs.close();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "Error:: read file not successfully" << std::endl;
		}
		return  std::move(code);
	}
}