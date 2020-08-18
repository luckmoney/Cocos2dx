#pragma once
#ifndef _MODEL_H
#define _MODEL_H

#include <string>
#include <vector>
#include "Shader.h"
#include "Mesh.h"

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "dev_common.h"

class Model {
public:

	vector<Texture> textures_loaded;
	vector<Mesh> meshees;
	string directory;
	bool gammaCorrection;

	Model(string const &path,bool gamms = false);

	void Draw(Shader &shader);

private:
	void loadModel(string const &path);

	void processNode(aiNode *node, const aiScene* scene);

	Mesh processMesh(aiMesh *mesh, const aiScene *scene);

	vector<Texture> loadMaterialTextures(aiMaterial* mat,aiTextureType type, string typeName);

};

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
#endif
