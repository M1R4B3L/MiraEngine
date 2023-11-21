#pragma once

#include "Module.h"
#include "Math/float3.h"

namespace tinygltf
{
	struct Model;
	struct Mesh;
	struct Primitive;
}

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
	unsigned mat;

	unsigned numVert = 0;
	unsigned numInd = 0;

	const float* bufferPos = nullptr;
	const float* bufferTexCoord = nullptr;
	const float* bufferNorm = nullptr;
	unsigned buffSize = 0;

	void CreateVAO();
	void Draw(const std::vector<unsigned>& textures);
	void LoadMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void LoadMaterials(const tinygltf::Model& srcModel, const char* imagePath);
};

class ModuleModel : public Module
{public:

	ModuleModel();
	~ModuleModel() override;

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	void LoadModel(const char* path);

	std::vector<unsigned> textures;
	std::vector<Mesh*> meshes;
};
