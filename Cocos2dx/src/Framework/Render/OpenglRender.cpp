#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Framework/Render/OpenglRender.h"


namespace Cocos {
	RenderSystem *g_RenderSystem = static_cast<RenderSystem*>(new OpenglRender);

	std::unordered_map<std::string,uint32_t> m_Textures;

	void checkGLerror(std::string description) {
		GLenum error = glGetError();
		while (error != GL_NO_ERROR)
		{
			switch (error) {
			case(GL_NO_ERROR):
				break;
			case(GL_INVALID_ENUM):
				std::cout <<"error :: "<< description << ": GL_INVALID_ENUM";
				break;
			case(GL_INVALID_VALUE):
				std::cout << "error :: " << description << ": GL_INVALID_VALUE";
				break;
			case(GL_INVALID_OPERATION):
				std::cout << "error :: " << description << ": GL_INVALID_OPERATION";
				break;
			case(GL_INVALID_FRAMEBUFFER_OPERATION):
				std::cout << "error :: " << description << ": GL_INVALID_FRAMEBUFFER_OPERATION";
				break;
			case(GL_OUT_OF_MEMORY):
				std::cout << "error :: " << description << ": GL_OUT_OF_MEMORY";
				break;
			default:
				std::cout << "error :: " << description << ": Unknown error!";
			}
			error = glGetError();

		}
	}

	void OpenglRender::BeginScene() {
		RenderSystem::BeginScene();

		InitGeometries();
		if (g_SceneSystem->SkyBox)
		{
			initializeSkyBox();
		}
	}

	void OpenglRender::EndScene() {
		for (auto &buffer_id:m_buffers )
		{
			glDeleteBuffers(1, &buffer_id);
		}
		m_buffers.clear();

		for (int i = 0 ; i < m_Frames.size();i++)
		{
			if (m_uboLightInfo[i])
			{
				glDeleteBuffers(1,&m_uboLightInfo[i]);
				m_uboLightInfo[i] = 0;
			}
		}
	}

	void OpenglRender::BeginFrame(const Frame &frame) {
		glClearColor(0.3, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SetPerFrameConstants(frame.frameContext);
		SetLightInfo(frame.lightInfo);
	}

	void OpenglRender::EndFrame() {

	}

	void OpenglRender::SetPerFrameConstants(const DrawFrameContext& context) {
		if (!m_uboDrawFrameConstant[m_nFrameIndex])
		{
			glGenBuffers(1, &m_uboDrawFrameConstant[m_nFrameIndex]);
		}
		glBindBuffer(GL_UNIFORM_BUFFER, m_uboDrawFrameConstant[m_nFrameIndex]);
		auto constants = static_cast<PerFrameConstants>(context);
		glBufferData(GL_UNIFORM_BUFFER, kSizePerFrameConstantBuffer, &constants, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}


	void OpenglRender::SetLightInfo(const LightInfo& lightInfo) {
		if (!m_uboLightInfo[m_nFrameIndex])
		{
			glGenBuffers(1,&m_uboLightInfo[m_nFrameIndex]);
		}
		glBindBuffer(GL_UNIFORM_BUFFER,m_uboLightInfo[m_nFrameIndex]);
		glBufferData(GL_UNIFORM_BUFFER,kSizeLightInfo,&lightInfo,GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER,0);
	}



	int32_t upload_texture(std::shared_ptr<SceneObjectTexture> texture) {
		std::string texture_key = texture->GetName();
		GLuint texture_id;
		auto it = m_Textures.find(texture_key);
		if (it == m_Textures.end()) {
			glGenTextures(1,&texture_id);

			auto data = texture->GetTextureImage();
			if (data) {
				GLenum format;
				auto nrComponent = texture->GetComponent();
				if (nrComponent == 1)
				{
					format = GL_RED;
				}
				else if (nrComponent == 3) {
					format = GL_RGB;
				}
				else if (nrComponent == 4){
					format = GL_RGBA;
				}
				int width = texture->GetWidth();
				int height = texture->GetHeight();
				glBindTexture(GL_TEXTURE_2D,texture_id);
				glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				texture->FreeImage();
			}

			m_Textures[texture_key] = texture_id;
		}
		else {
			texture_id = it->second;
		}

		return texture_id;
	};

	void OpenglRender::InitGeometries() {
		auto geoVec = g_SceneSystem->GetGeometries();
		for (auto &object: geoVec)
		{
			auto object_mesh_vec = object.second->GetMeshArrary();
			for (auto &mesh : object_mesh_vec)
			{
				GLuint vao;
				glGenVertexArrays(1, &vao);
				glBindVertexArray(vao);

				uint32_t mode;
				auto m_type = mesh.GetType();
				switch (m_type)
				{
				case Cocos::MeshPrimitiveType::kPrimitiveTypePointList:
					mode = GL_POINT;
					break;
				case Cocos::MeshPrimitiveType::kPrimitiveTypeLineList:
					mode = GL_LINE;
					break;
				case Cocos::MeshPrimitiveType::kPrimitiveTypeTriList:
					mode = GL_TRIANGLES;
					break;
				default:
					break;
				}

				auto vertex_vec = mesh.GetSceneVertexArrary();	
				unsigned int idx = 0;

				for (auto &vertex: vertex_vec)
				{
					GLuint vbo;
					glGenBuffers(1, &vbo);
					glBindBuffer(GL_ARRAY_BUFFER, vbo);
					glBufferData(GL_ARRAY_BUFFER, vertex.GetSize(), vertex.GetData(), GL_STATIC_DRAW);
					glEnableVertexAttribArray(idx);
					m_buffers.push_back(vbo);
					auto type = vertex.GetDataType();
					switch (type)
					{
					case Cocos::VertexType::Float1:
						glVertexAttribPointer(idx, 1, GL_FLOAT, GL_FALSE, 0, nullptr);
						break;
					case Cocos::VertexType::Float2:
						glVertexAttribPointer(idx, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
						break;
					case Cocos::VertexType::Float3:
						glVertexAttribPointer(idx, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
						break;
					case Cocos::VertexType::Float4:
						glVertexAttribPointer(idx, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
						break;
					default:
						break;
					}
					++idx;
				}

				auto index_vec = mesh.GetSceneIndexArrary();
				for (auto &Index:index_vec)
				{
					GLuint ibo;
					glGenBuffers(1, &ibo);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, Index.GetSize(), Index.GetData(), GL_STATIC_DRAW);

					uint32_t type;
					auto index_type = Index.GetType();
					switch (index_type)
					{
					case IndexType::kIndexDataTypeInt8:
						type = GL_UNSIGNED_BYTE;
						break;
					case IndexType::kIndexDataTypeInt16:
						type = GL_UNSIGNED_SHORT;
						break;
					case IndexType::kIndexDataTypeInt32:
						type = GL_UNSIGNED_INT;
					default:
						break;
					}

			
					DrawBatchContext dbc;
					dbc.vao = vao;
					dbc.mode = mode;
					dbc.count = Index.GetCount();
					dbc.type = type;

					auto mt_index = Index.GetMaterialIndex();
					auto material = g_SceneSystem->m_Materials[mt_index];
					const auto& color = material->GetBaseColor();
					if (color.ValueMap)
					{
						dbc.material.diffuseMap = upload_texture(color.ValueMap);
					}

					const auto& normal = material->GetNormal();
					if (normal.ValueMap)
					{
						dbc.material.normalMap = upload_texture(normal.ValueMap);
					}
					
					const auto& specular = material->GetSpecularColor();
					if (specular.ValueMap)
					{
						dbc.material.specularMap = upload_texture(specular.ValueMap);
					}

					for (unsigned int i = 0; i < m_Frames.size(); ++i)
					{
						m_Frames[i].m_batchContext.push_back(dbc);
					}
				}

				glBindVertexArray(0);

			}
		}

	}

	void OpenglRender::initializeSkyBox() {
		uint32_t texture_id;
		const size_t kMaxMipLevels = 10;
		glGenTextures(1,&texture_id);
		GLenum target = GL_TEXTURE_CUBE_MAP;
		glBindTexture(target,texture_id);

		for (unsigned int i = 0 ; i < 6;i++)
		{
			auto &texture = g_SceneSystem->SkyBox->GetTexture(i);
			auto data = texture.GetTextureImage();
			if (data)
			{
				auto w = texture.GetWidth();
				auto h = texture.GetHeight();
				
				GLenum format;
				auto nrComponent = texture.GetComponent();
				if (nrComponent == 1)
				{
					format = GL_RED;
				}
				else if (nrComponent == 3) {
					format = GL_RGB;
				}
				else if (nrComponent == 4) {
					format = GL_RGBA;
				}

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
				texture.FreeImage();
			}
		}

		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


		m_Textures["SkyBox"] = texture_id;

		uint32_t skyboxVAO, skyboxVBO[2];
		glGenVertexArrays(1,&skyboxVAO);
		glGenBuffers(2,skyboxVBO);
		glBindVertexArray(skyboxVAO);
		glBindBuffer(GL_ARRAY_BUFFER,skyboxVBO[0]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),skyboxVertices,GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,skyboxVBO[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(skyboxIndices),skyboxIndices,GL_STATIC_DRAW);
		glBindVertexArray(0);
		m_buffers.push_back(skyboxVBO[0]);
		m_buffers.push_back(skyboxVBO[1]);

		m_SkyBoxDrawBatchContext.material.aoMap = texture_id;
		m_SkyBoxDrawBatchContext.vao = skyboxVAO;
		m_SkyBoxDrawBatchContext.mode = GL_TRIANGLES;
		m_SkyBoxDrawBatchContext.type = GL_UNSIGNED_BYTE;
		m_SkyBoxDrawBatchContext.count = sizeof(skyboxIndices) / sizeof(skyboxIndices[0]);
		
		checkGLerror("skybox");
	}

	bool OpenglRender::setShaderParameter(const char* paramName, const uint32_t param) {
		unsigned int location;
		location = glGetUniformLocation(m_CurrentShader,paramName);
		if (location ==-1)
		{
			return false;
		}
		glUniform1i(location,(int)param);
		return true;
	}

	bool OpenglRender::setShaderParameter(const char* paramName, const glm::mat4& mat) {
		unsigned int location;
		location = glGetUniformLocation(m_CurrentShader, paramName);
		if (location == -1)
		{
			return false;
		}
		glUniformMatrix4fv(location,1,GL_FALSE,&mat[0][0]);
		return true;
	}


	void OpenglRender::DrawPoint()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);

		glBindVertexArray(vao);

		GLuint buffer_id;
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

		float arr[3]{0,0,0};
		glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

		glDrawArrays(GL_POINT, 0x00, 1);

		m_buffers.push_back(buffer_id);
	}

	void OpenglRender::DrawLine()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);

		glBindVertexArray(vao);

		GLuint buffer_id;
		m_buffers.push_back(buffer_id);

		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

		float arr[]{ -0.5,0,0,0.5,0,0 };
		glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3, GL_FLOAT, false, 0, nullptr);

		glDrawArrays(GL_LINE, 0x00, 2);
	}

	void OpenglRender::DrawTriangle()
	{
		GLuint vao;
		glGenVertexArrays(1, &vao);

		glBindVertexArray(vao);

		GLuint buffer_id;
		glGenBuffers(1, &buffer_id);
		glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
		m_buffers.push_back(buffer_id);

		float arr[]{ -0.5,0,0,0.5,0,0,0,0.5,0 };
		glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

		glDrawArrays(GL_TRIANGLES, 0x00, 3);
	}

	void OpenglRender::DrawGeometry() {
		this->DrawPoint();
	}

	void OpenglRender::DrawSkyBox()
	{
		setShaderParameter("skybox", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyBoxDrawBatchContext.material.aoMap);

		glBindVertexArray(m_SkyBoxDrawBatchContext.vao);
		glDrawElements(m_SkyBoxDrawBatchContext.mode,m_SkyBoxDrawBatchContext.count,m_SkyBoxDrawBatchContext.type,nullptr);
		glBindVertexArray(0);

		checkGLerror("draw sky box");
	}

	void OpenglRender::DrawTerrain()
	{

	}



	void OpenglRender::DrawBatch(Frame& frame)
	{
		for (auto &context:frame.m_batchContext)
		{
			setShaderParameter("texture_diffuse_map", 0);
			glActiveTexture(GL_TEXTURE0);
			if (context.material.diffuseMap > 0)
			{
				glBindTexture(GL_TEXTURE_2D,context.material.diffuseMap);
			}
			else {
				glBindTexture(GL_TEXTURE_2D,0);
			}
			setShaderParameter("texture_normal_map", 1);
			glActiveTexture(GL_TEXTURE1);
			if (context.material.normalMap > 0)
			{
				glBindTexture(GL_TEXTURE_2D,context.material.normalMap);
			}
			else {
				glBindTexture(GL_TEXTURE_2D,0);
			}
			setShaderParameter("texture_metallic_map",2);
			glActiveTexture(GL_TEXTURE2);
			if (context.material.metallicMap > 0)
			{
				glBindTexture(GL_TEXTURE_2D,context.material.metallicMap);
			}
			else {
				glBindTexture(GL_TEXTURE_2D,0);
			}
			setShaderParameter("texture_specular_map",3);
			glActiveTexture(GL_TEXTURE3);
			if (context.material.specularMap > 0 )
			{
				glBindTexture(GL_TEXTURE_2D,context.material.specularMap);
			}
			else {
				glBindTexture(GL_TEXTURE_2D,0);
			}
			setShaderParameter("texture_height_map", 4);
			glActiveTexture(GL_TEXTURE4);
			if (context.material.heightMap > 0)
			{
				glBindTexture(GL_TEXTURE_2D,context.material.heightMap);
			}
			else{
				glBindTexture(GL_TEXTURE_2D,0);
			}


			glBindVertexArray(context.vao);
			glDrawElements(context.mode, context.count, context.type, nullptr);
		}
		glBindVertexArray(0);
	}


	void OpenglRender::SetPipelineState(PipelineState* pipelineState,const Frame& frame)
	{
		m_CurrentShader = pipelineState->shaderProgram;

		glUseProgram(m_CurrentShader);

		switch (pipelineState->depthTestMode)
		{
		case DEPTH_TEST_MODE::NONE:
			glDisable(GL_DEPTH_TEST);
			break;
		case DEPTH_TEST_MODE::LARGE:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_GREATER);
			break;
		case DEPTH_TEST_MODE::LARGE_EQUAL:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_GEQUAL);
			break;
		case DEPTH_TEST_MODE::LESS:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			break;
		case DEPTH_TEST_MODE::LESS_EQUAL:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			break;
		case DEPTH_TEST_MODE::EQUAL:
			glEnable(GL_DEPTH_TEST);
			break;
		case DEPTH_TEST_MODE::NOT_EQUAL:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_NOTEQUAL);
			break;
		case DEPTH_TEST_MODE::NEVER:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_NEVER);
			break;
		case DEPTH_TEST_MODE::ALWAYS:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_ALWAYS);
			break;
		default:
			assert(0);
		}


		switch (pipelineState->cullFaceMode)
		{
		case CULL_FACE_MODE::NONE:
			glDisable(GL_CULL_FACE);
			break;
		case CULL_FACE_MODE::BACK:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			break;
		case CULL_FACE_MODE::FRONT:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			break;
		default:
			assert(0);
		}

		if (pipelineState->bDepthWrite)
		{
			glDepthMask(GL_TRUE);
		}
		else {
			glDepthMask(GL_FALSE);
		}



		uint32_t blockIndex = glGetUniformBlockIndex(m_CurrentShader, "LightInfo");
		if (blockIndex != GL_INVALID_INDEX)
		{
			int32_t blockSize;
			glGetActiveUniformBlockiv(m_CurrentShader,blockIndex,GL_UNIFORM_BLOCK_DATA_SIZE,&blockSize);

			assert(blockSize >= sizeof(LightInfo));

			glUniformBlockBinding(m_CurrentShader,blockIndex,12);
			glBindBufferBase(GL_UNIFORM_BUFFER,12,m_uboLightInfo[frame.frameIndex]);
		}

		blockIndex = glGetUniformBlockIndex(m_CurrentShader, "PerFrameConstants");
		if (blockIndex != GL_INVALID_INDEX)
		{
			int32_t blockSize;
			glGetActiveUniformBlockiv(m_CurrentShader, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);
			assert(blockSize >= sizeof(PerBatchConstants));
			glUniformBlockBinding(m_CurrentShader, blockIndex, 11);
			glBindBufferBase(GL_UNIFORM_BUFFER, 11, m_uboDrawFrameConstant[frame.frameIndex]);
		}

	}


	void OpenglRender::BeginRenderToTexture(uint32_t texture_id,uint32_t width,uint32_t height,uint32_t framebuffer)   {

	}

	void OpenglRender::EndRenderToTexture() {

	}

	int32_t OpenglRender::GenerateShadowMapArray(const uint32_t width, const uint32_t height, const uint32_t count) {

		uint32_t shadowMap;
		glGenTextures(1, &shadowMap);
		glBindTexture(GL_TEXTURE_2D, shadowMap);
		glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);

		return static_cast<int32_t>(shadowMap);
	}


	void OpenglRender::BeginShadowMap(const int32_t light_index,const int32_t shadowmap,const uint32_t width,
									const uint32_t height, const int32_t layer_idex,const Frame& frame){

		glGenFramebuffers(1, &m_ShadowMapFramebufferName);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowMapFramebufferName);
	
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, (uint32_t)shadowmap, 0);
	
		auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << std::hex << (status) << std::endl;
			assert(0);
		}
		glDrawBuffer(GL_NONE);

		glViewport(0, 0, width, height);
		glDrawBuffers(0, nullptr);
		if (frame.lightInfo.lights[light_index].lightType != LightType::Omni || layer_idex == 0)
		{
			glClear(GL_DEPTH_BUFFER_BIT);
		}
		float nearClipDistance = 1.0f;
		float farClipDistance = 100.0f;
		
		ShadowMapConstants constants;
		constants.light_index = light_index;
		constants.shadowmap_layer_index = static_cast<float>(layer_idex);
		constants.near_plane = nearClipDistance;
		constants.far_plane = farClipDistance;

		if (!m_uboShadowMatricesConstant[frame.frameIndex])
		{
			glGenBuffers(1, &m_uboShadowMatricesConstant[frame.frameIndex]);
		}
		glBindBuffer(GL_UNIFORM_BUFFER, m_uboShadowMatricesConstant[frame.frameIndex]);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(constants),&constants, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenglRender::EndShadowMap(const int32_t shadowmap, const int32_t layer_index){
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &m_ShadowMapFramebufferName);
		glViewport(0, 0, WINDOWSWIDTH, WINDOWSHEIGHT);
	}

	void OpenglRender::SetShadowMaps(const Frame& frame) {
		const float color[] = { 1.0f,1.0f,1.0f,1.0f };
		setShaderParameter("CombinedshadowMapsamp0", 7);
		glActiveTexture(GL_TEXTURE7);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		auto texture_id = frame.frameContext.shadowMap;
		if (texture_id > 0)
		{
			glBindTexture(GL_TEXTURE_2D, (GLuint)texture_id);
		}

		setShaderParameter("CombinedglobalShadowMapsamp0", 8);
		glActiveTexture(GL_TEXTURE8);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
		texture_id = frame.frameContext.globalShadowMap;
		if (texture_id > 0)
		{
			glBindTexture(GL_TEXTURE_2D, (GLuint)texture_id);
		}

		setShaderParameter("CombinedcubeShadowMapsamp0", 9);
		glActiveTexture(GL_TEXTURE9);
		GLenum target = GL_TEXTURE_2D;
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		texture_id = frame.frameContext.cubeShadowMap;
		if (texture_id > 0)
		{
			glBindTexture(target, (GLuint)texture_id);
		}
	}
}