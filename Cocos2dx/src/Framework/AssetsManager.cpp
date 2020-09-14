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

	void processNode(aiNode* node, const aiScene* scene, SceneObject&);
	SceneMesh processMesh(aiMesh* mesh, const aiScene* scene);

	bool AssetsManager::loadModel(const char* path) {

		std::string path_str = std::string(path);

		Assimp::Importer importer;
		const aiScene*scene = importer.ReadFile(path_str, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "error ::assimp::" << importer.GetErrorString() << std::endl;
			return false;
		}
		std::string directory = path_str.substr(0, path_str.find_last_of('/'));
		SceneObject obj;
		processNode(scene->mRootNode, scene,obj);
		g_SceneSystem->AddObject(obj);
		return true;
	}

	void processNode(aiNode* node, const aiScene* scene, SceneObject&obj) {

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			SceneMesh smesh = processMesh(mesh, scene);
			obj.AddMesh(std::move(smesh));
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
		SceneIndexArrary indexArr(index_data, index_size * sizeof(unsigned int), IndexType::kIndexDataTypeInt32);
		sc_mesh.AddIndexArrary(std::move(indexArr));

		return std::move(sc_mesh);
	}

}