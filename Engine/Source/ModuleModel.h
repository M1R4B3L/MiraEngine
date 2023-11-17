#pragma once

#include "Module.h"
#include "Math/float3.h"

namespace tinygltf
{
	struct Model;
	struct Mesh;
	struct Primitive;
}

struct Mesh
{

	unsigned vbo;
	unsigned ebo;
	unsigned mat;

	unsigned numVert = 0;
	unsigned numInd = 0;

	const float* bufferPos = nullptr;
	const float* bufferTexCoord = nullptr;
	unsigned buffSize = 0;

	void CreateVAO();
	void Draw(const std::vector<unsigned>& textures);
	void LoadMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
};

class ModuleModel : public Module
{public:

	ModuleModel();
	~ModuleModel() override;

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	void LoadModel(const char* path);
	void LoadMaterials(const tinygltf::Model& srcModel);

	unsigned vao;
	std::vector<unsigned> textures;
	std::vector<Mesh*> meshes;
};
