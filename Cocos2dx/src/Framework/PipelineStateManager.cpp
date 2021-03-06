#pragma once 

#include <glad/glad.h>
#include "Framework/PipelineStateManager.h"
#include <iostream>

namespace Cocos {
	PipelineStateManager *g_PipelineManager = new PipelineStateManager();


	int PipelineStateManager::Initialize() {

		PipelineState geoPipeline;
		geoPipeline.pipelineStateName = "Basic";
		geoPipeline.vertexShaderName = "../Cocos2dx/shader/basic.vs";
		geoPipeline.pixelShaderName =  "../Cocos2dx/shader/basic.fs";
		geoPipeline.cullFaceMode = CULL_FACE_MODE::BACK;
		geoPipeline.depthTestMode = DEPTH_TEST_MODE::LESS_EQUAL;
		geoPipeline.bDepthWrite = true;
		
		registerPipelineState(geoPipeline);


		PipelineState skyboxPipeline;
		skyboxPipeline.pipelineStateName = "SkyBox";
		skyboxPipeline.vertexShaderName = "../Cocos2dx/shader/skybox.vs";
		skyboxPipeline.pixelShaderName =  "../Cocos2dx/shader/skybox.fs";
		skyboxPipeline.cullFaceMode = CULL_FACE_MODE::BACK;
		skyboxPipeline.depthTestMode = DEPTH_TEST_MODE::LESS_EQUAL;
		skyboxPipeline.bDepthWrite = true;
		registerPipelineState(skyboxPipeline);

		PipelineState pipelineState;
		pipelineState.pipelineStateName = "Omni_Light_Shadow_Map";
		pipelineState.vertexShaderName = "../Cocos2dx/shader/shadowmap_omni.vs";
		pipelineState.pipelineStateName = "../Cocos2dx/shader/shadowmap_omni.fs";
		pipelineState.cullFaceMode = CULL_FACE_MODE::FRONT;
		pipelineState.pixelFormat = PIXEL_FORMAT::INVALID;
		registerPipelineState(pipelineState);


		pipelineState.pipelineStateName = "Spot_Light_Shadow_Map";
		pipelineState.vertexShaderName = "../Cocos2dx/shader/shadowmap_spot.vs";
		pipelineState.pipelineStateName = "../Cocos2dx/shader/shadowmap_spot.fs";
		registerPipelineState(pipelineState);

		pipelineState.pipelineStateName = "Area_Light_Shadow_Map";
		pipelineState.vertexShaderName = "../Cocos2dx/shader/shadowmap_spot.vs";
		pipelineState.pipelineStateName = "../Cocos2dx/shader/shadowmap_spot.fs";
		registerPipelineState(pipelineState);

		pipelineState.pipelineStateName = "Sun_Light_Shadow_Map";
		pipelineState.vertexShaderName = "../Cocos2dx/shader/shadowmap_spot.vs";
		pipelineState.pipelineStateName = "../Cocos2dx/shader/shadowmap_spot.fs";
		registerPipelineState(pipelineState);

		return 0;
	}

	void PipelineStateManager::Finalize()
	{
	
	}

	PipelineState& PipelineStateManager::GetPipelineState(const std::string& pipeline_name) {
		auto iter = m_pipeline_map.find(pipeline_name);
		if (iter != m_pipeline_map.end())
		{
			return iter->second;
		}
		return m_pipeline_map.begin()->second;
	}

	bool PipelineStateManager::registerPipelineState(PipelineState& pipelineState)
	{

		pipelineState.shaderProgram = glCreateProgram();
		if (!pipelineState.vertexShaderName.empty())
		{
			std::string vStr = g_AssetsManager->readTextFromFile(pipelineState.vertexShaderName.c_str());
			const char *vCode = vStr.c_str();
			GLint vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vCode, NULL);
			glCompileShader(vertex);
			checkCompileErrors(vertex, "VERTEX");
			glAttachShader(pipelineState.shaderProgram, vertex);
			glDeleteShader(vertex);
		}
		if (!pipelineState.pixelShaderName.empty())
		{
			std::string fStr = g_AssetsManager->readTextFromFile(pipelineState.pixelShaderName.c_str());
			const char *fCode = fStr.c_str();
			GLint fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fCode, NULL);
			glCompileShader(fragment);
			checkCompileErrors(fragment, "FRAGMENT");
			glAttachShader(pipelineState.shaderProgram, fragment);
			glDeleteShader(fragment);
		}
		glLinkProgram(pipelineState.shaderProgram);

		m_pipeline_map.insert(std::make_pair(pipelineState.pipelineStateName, std::move(pipelineState)));
		return true;
	}

	void PipelineStateManager::checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		const int length = 1024;
		char infoLog[length];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, length, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type.c_str() << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, length, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: "<< type.c_str()<< "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}

}