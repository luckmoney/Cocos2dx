#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>; // ����glad����ȡ���еı���OpenGLͷ�ļ�

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Shader
{
public:
	// ����ID
	unsigned int ID;


	// ��������ȡ��������ɫ��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);


	Shader(const GLchar* vertexPath, const GLchar* geometryPath,const GLchar* fragmentPath);

	// ʹ��/�������
	void use();
	// uniform���ߺ���
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;


	void setVec2(const std::string & name, const glm::vec2 & value) const;

	void setVec2(const std::string & name, float x, float y) const;

	void setVec3(const std::string & name, const glm::vec3 & value) const;

	void setVec3(const std::string & name, float x, float y, float z) const;

	void setVec4(const std::string & name, const glm::vec4 & value) const;

	void setVec4(const std::string & name, float x, float y, float z, float w);

	void setMat2(const std::string & name, const glm::mat2 & mat) const;

	void setMat3(const std::string & name, const glm::mat3 & mat) const;

	void setMat4(const std::string & name, const glm::mat4 & mat) const;


private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif

