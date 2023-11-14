#pragma once

#include "Module.h"

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

	void LoadMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
};

class ModuleModel : public Module
{public:

	ModuleModel();
	~ModuleModel() override;

	bool Init() override;
	bool CleanUp() override;

	void LoadModel(const char* path);


};
