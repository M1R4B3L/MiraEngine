#include "Globals.h"
#include "ModuleModel.h"

#include "GL/glew.h"
#include "Math/float3.h"

#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE
#define TINYGLTF_IMPLEMENTATION

#include "External/tinygltf-2.8.18/tiny_gltf.h"


ModuleModel::ModuleModel()
{
}

ModuleModel::~ModuleModel()
{
}

bool ModuleModel::Init()
{
    bool ret = true;

    //LoadModel("Models/Triangle/TriangleWithoutIndices.gltf");
    return ret;
}

bool ModuleModel::CleanUp()
{
    return true;
}

void ModuleModel::LoadModel(const char* path)
{
    tinygltf::TinyGLTF gltfContext;
    tinygltf::Model model;
    std::string error, warning;
    bool loadOk = gltfContext.LoadASCIIFromFile(&model, &error, &warning, path);
    if (!loadOk)
    {
        LOG("Error loading %s: %s", path, error.c_str());
    }

    for (const auto& srcMesh : model.meshes)
    {
        for (const auto& primitive : srcMesh.primitives)
        {
            Mesh* mesh = new Mesh;
            mesh->LoadMesh(model, srcMesh, primitive);
        }
    }


}

void Mesh::LoadMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
{
    const auto& itPos = primitive.attributes.find("POSITION");
    if (itPos != primitive.attributes.end())
    {
        const tinygltf::Accessor& posAcc = model.accessors[itPos->second];
        assert(posAcc.type == TINYGLTF_TYPE_VEC3);
        assert(posAcc.componentType == GL_FLOAT);
        const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
        const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];
        const unsigned char* bufferPos = &(posBuffer.data[posAcc.byteOffset + posView.byteOffset]);

        glGenBuffers(1, &vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * posAcc.count, nullptr, GL_STATIC_DRAW);

        float3* ptr = reinterpret_cast<float3*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        for (size_t i = 0; i < posAcc.count; ++i)
        {
            ptr[i] = *reinterpret_cast<const float3*>(bufferPos);
            bufferPos += posView.byteStride;
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

}
