#include "Framework/AssetsManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Framework/Base/SceneMesh.h"

namespace Cocos {
	AssetsManager *g_AssetsManager = new AssetsManager();

	std::string g_directory("");

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

	void processNode(aiNode* node, const aiScene* scene, std::shared_ptr<SceneObject>);
	SceneMesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::shared_ptr<SceneObject> AssetsManager::loadModel(const char* path) {

		std::string path_str = std::string(path);

		Assimp::Importer importer;
		const aiScene*scene = importer.ReadFile(path_str, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "error ::assimp::" << importer.GetErrorString() << std::endl;
			return nullptr;
		}
		g_directory = path_str.substr(0, path_str.find_last_of('/'));
		std::shared_ptr<SceneObject> obj = std::make_shared<SceneObject>();
		processNode(scene->mRootNode, scene,obj);
		g_SceneSystem->AddObject(obj);
		return obj;
	}

	void processNode(aiNode* node, const aiScene* scene, std::shared_ptr<SceneObject> obj) {

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			SceneMesh smesh = processMesh(mesh, scene);
			obj->AddMesh(std::move(smesh));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene,obj);
		}

	}

	SceneMesh processMesh(aiMesh* mesh, const aiScene*scene) {
		SceneMesh sc_mesh;

		switch (mesh->mPrimitiveTypes)
		{
		case aiPrimitiveType::aiPrimitiveType_POINT:
			sc_mesh.Type(MeshPrimitiveType::kPrimitiveTypePointList);
			break;
		case aiPrimitiveType::aiPrimitiveType_LINE:
			sc_mesh.Type(MeshPrimitiveType::kPrimitiveTypeLineList);
			break;
		case aiPrimitiveType::aiPrimitiveType_TRIANGLE:
			sc_mesh.Type(MeshPrimitiveType::kPrimitiveTypeTriList);
			break;
		default:
			break;
		}

		uint32_t vertex_size = mesh->mNumVertices;
		auto vertex_buffer_size = vertex_size * 3;
		float* vertex_data = new float[vertex_buffer_size];
		memset(vertex_data, 0, vertex_buffer_size);
		memcpy(vertex_data, mesh->mVertices, vertex_buffer_size*sizeof(float));
		SceneVertexArrary verArr(vertex_data, vertex_buffer_size * sizeof(float), VertexType::Float3);
		sc_mesh.AddVertexArrary(std::move(verArr));


		float* normal_data = new float[vertex_buffer_size];
		memset(normal_data, 0, vertex_buffer_size);
		memcpy(normal_data, mesh->mNormals, vertex_buffer_size * sizeof(float));
		SceneVertexArrary norArr(normal_data,vertex_buffer_size*sizeof(float),VertexType::Float3);
		sc_mesh.AddVertexArrary(std::move(verArr));

		auto tc_size = vertex_size * 2;
		float* texCoord_data = new float[tc_size];
		float* texCoord_ptr = texCoord_data;
		memset(texCoord_data, 0, tc_size);
		for (unsigned int i = 0 ; i < vertex_size;i++)
		{
			*texCoord_ptr = mesh->mTextureCoords[0][i].x;
			*(texCoord_ptr + 1) = mesh->mTextureCoords[0][i].y;
			texCoord_ptr += 2;
		}
		SceneVertexArrary txcArr(texCoord_data, tc_size * sizeof(float), VertexType::Float2);
		sc_mesh.AddVertexArrary(std::move(txcArr));


		unsigned int face_size = mesh->mNumFaces;
		unsigned int index_size = face_size * 3;

		unsigned int * index_data = new unsigned int[index_size];
		memset(index_data, 0, index_size);
		unsigned int * index_ptr = index_data;

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			memcpy(index_ptr, face.mIndices, 3 * sizeof(unsigned int));
			index_ptr += 3;
		}

		auto material_index = mesh->mMaterialIndex;
		std::string index_str = std::to_string(material_index);

		SceneIndexArrary indexArr(index_data, index_size * sizeof(unsigned int), IndexType::kIndexDataTypeInt32, index_str.c_str());
		sc_mesh.AddIndexArrary(std::move(indexArr));


		auto sc_Material = std::make_shared<SceneObjectMaterial>(index_str);

		aiMaterial* material = scene->mMaterials[material_index];
		aiString str;
		aiTextureType type = aiTextureType_DIFFUSE;
		for (unsigned int i = 0 ; i < material->GetTextureCount(type);i++)
		{
			aiString str;
			material->GetTexture(type, i, &str);
			sc_Material->SetName(index_str);
			sc_Material->SetTexture("diffuse", g_directory + '/' + str.C_Str());
		}
		
		type = aiTextureType_SPECULAR;
		for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
		{
			aiString str;
			material->GetTexture(type, i, &str);
			sc_Material->SetName(index_str);
			sc_Material->SetTexture("specular", g_directory + '/' + str.C_Str());
		}

		type = aiTextureType_HEIGHT;
		for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
		{
			aiString str;
			material->GetTexture(type, i, &str);
			sc_Material->SetName(index_str);
			sc_Material->SetTexture("normal", g_directory + '/' + str.C_Str());
		}

		type = aiTextureType_AMBIENT;
		for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
		{
			aiString str;
			material->GetTexture(type, i, &str);
			sc_Material->SetName(index_str);
			sc_Material->SetTexture("height", g_directory + '/' + str.C_Str());
		}

		g_SceneSystem->m_Materials.insert(std::make_pair(index_str,sc_Material));


		return std::move(sc_mesh);
	}

}