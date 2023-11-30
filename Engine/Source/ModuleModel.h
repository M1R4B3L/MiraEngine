#pragma once

#include "Module.h"
#include "Math/float3.h"

namespace tinygltf
{
	class Model;
	struct Mesh;
	struct Primitive;
}

struct Texture;

//TODO GAMEOBJECT 
/*
float4x4 Model 
unsigned textureId // array for each texture diffuse,normals,etc
unsigned vao
*/

struct Mesh
{
	unsigned vao;
	unsigned vbo;
	unsigned ebo;

	unsigned numVert = 0;
	unsigned numInd = 0;

	const float* bufferPos = nullptr;
	const float* bufferTexCoord = nullptr;
	const float* bufferNorm = nullptr;

	unsigned stridePos = 0;
	unsigned strideNorm = 0;

	unsigned buffSize = 0;

	unsigned disffuseMat;

	void CreateVAO();
	void Draw(const std::vector<Texture*>& textures);
	void LoadMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void LoadVBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
};

class ModuleModel : public Module
{public:

	ModuleModel();
	~ModuleModel();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	void LoadModel(const char* path);
	void LoadMaterials(const tinygltf::Model& srcModel, const char* imagePath);

	std::vector<Texture*> textures;
	std::vector<Mesh*> meshes;
};
