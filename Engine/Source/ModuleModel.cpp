#include "Globals.h"
#include "Application.h"
#include "ModuleModel.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"

#include "GL/glew.h"
#include "Math/float3.h"
#include "Math/float2.h"

#define TINYGLTF_IMPLEMENTATION

#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE


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

    LoadModel("Models/BakerHouse/BakerHouse.gltf");
    return ret;
}

update_status ModuleModel::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleModel::CleanUp()
{
    glDeleteVertexArrays(1, &vao);

    for (int i = 0; i < App->model->meshes.size(); ++i)
    {
        glDeleteBuffers(1, &meshes[i]->vbo);
        glDeleteBuffers(1, &meshes[i]->ebo);
    }

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
            Mesh* mesh = new Mesh();
            mesh->CreateVAO();
            mesh->LoadMesh(model, srcMesh, primitive);
            mesh->LoadEBO(model, srcMesh, primitive);
            meshes.push_back(mesh);
        }
    }

    if(model.materials.size() > 0)
        LoadMaterials(model);
}

void ModuleModel::LoadMaterials(const tinygltf::Model& srcModel)
{
    for (const auto& srcMaterial : srcModel.materials)
    {
        unsigned int textureId = 0;
        if (srcMaterial.pbrMetallicRoughness.baseColorTexture.index >= 0)
        {
            const tinygltf::Texture& texture = srcModel.textures[srcMaterial.pbrMetallicRoughness.baseColorTexture.index];
            const tinygltf::Image& image = srcModel.images[texture.source];
            std::string temp = "Models/BakerHouse/";
            temp = temp + image.uri.c_str();
            textureId = App->renderExercise->CreateTexture(temp.c_str());
        }
        textures.push_back(textureId);
    }
}

void Mesh::LoadMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
{
    const auto& itPos = primitive.attributes.find("POSITION");
    const auto& itNorm = primitive.attributes.find("NORMAL");
    const auto& itTang = primitive.attributes.find("TANGENT");
    const auto& itTexCoord = primitive.attributes.find("TEXCOORD_0");

    if (itPos != primitive.attributes.end())
    {
        const tinygltf::Accessor& posAcc = model.accessors[itPos->second];
        assert(posAcc.type == TINYGLTF_TYPE_VEC3);
        assert(posAcc.componentType == GL_FLOAT);
        const tinygltf::BufferView& posBufferView = model.bufferViews[posAcc.bufferView];
        const tinygltf::Buffer& posBuffer = model.buffers[posBufferView.buffer];

        numVert = posAcc.count;

        bufferPos = reinterpret_cast<const float*>(&posBuffer.data[posBufferView.byteOffset + posAcc.byteOffset]);  
    }

    if (itTexCoord != primitive.attributes.end())
    {
        const tinygltf::Accessor& texCoordAcc = model.accessors[itTexCoord->second];
        assert(texCoordAcc.type == TINYGLTF_TYPE_VEC2);
        assert(texCoordAcc.componentType == GL_FLOAT);
        const tinygltf::BufferView& texCoordBufferView = model.bufferViews[texCoordAcc.bufferView];
        const tinygltf::Buffer& texCoordBuffer = model.buffers[texCoordBufferView.buffer];

        bufferTexCoord = reinterpret_cast<const float*>(&texCoordBuffer.data[texCoordBufferView.byteOffset + texCoordAcc.byteOffset]);
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);   
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    if (bufferPos != nullptr)
    {
        buffSize = sizeof(float) * 3 * numVert;
    }
    if (bufferTexCoord != nullptr)
    {
        buffSize = (sizeof(float) * 3 + sizeof(float) * 2) * numVert;
    }

    glBufferData(GL_ARRAY_BUFFER, buffSize, nullptr, GL_STATIC_DRAW);
    float* ptr = (float*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

    for (size_t i = 0; i < numVert * 5; i += 5)
    {
        for (int j = 0; j < 3; ++j)
        {
            ptr[i + j] = *(bufferPos);
            LOG("Pos %f", ptr[i + j]);
            ++bufferPos;
        }

        if (bufferTexCoord != nullptr)
        {
            for (int j = 3; j < 5; ++j)
            {
                ptr[i + j] = *(bufferTexCoord);
                LOG("Tc %f", ptr[i + j]);
                ++bufferTexCoord;
            }
        }
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

}


void Mesh::LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
{
    if (primitive.indices >= 0)
    {
        const tinygltf::Accessor& indAcc = model.accessors[primitive.indices];
        const tinygltf::BufferView& indView = model.bufferViews[indAcc.bufferView];
        const unsigned char* buffer = &(model.buffers[indView.buffer].data[indAcc.byteOffset + indView.byteOffset]);

        numInd = indAcc.count;

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indAcc.count, nullptr, GL_STATIC_DRAW);
        unsigned int* ptr = reinterpret_cast<unsigned int*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));

        if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT)
        {
            const uint32_t* bufferInd = reinterpret_cast<const uint32_t*>(buffer);
            for (uint32_t i = 0; i < indAcc.count; ++i)
                ptr[i] = bufferInd[i];
        }
        // TODO indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT
        if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT)
        {
            const uint16_t* bufferInd = reinterpret_cast<const uint16_t*>(buffer);
            for (uint16_t i = 0; i < indAcc.count; ++i)
            {
                ptr[i] = bufferInd[i];
                LOG("%u", bufferInd[i]);
            }          
        }
        //TODO indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE
        if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE)
        {
            const uint8_t* bufferInd = reinterpret_cast<const uint8_t*>(buffer);
            for (uint8_t i = 0; i < indAcc.count; ++i)
                ptr[i] = bufferInd[i];
        }

        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3 + sizeof(float) * 2, (void*)(sizeof(float) * 3));


    glBindVertexArray(0);
}

void Mesh::CreateVAO()
{
    glGenVertexArrays(1, &App->model->vao);
    glBindVertexArray(App->model->vao);
}

void Mesh::Draw(const std::vector<unsigned>& textures)
{
    glBindVertexArray(App->model->vao);

    glUseProgram(App->program->programId);
    if (!textures.empty())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
    }
 
    if(numInd > 0)
        glDrawElements(GL_TRIANGLES, numInd, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_TRIANGLES, 0, numVert);
}