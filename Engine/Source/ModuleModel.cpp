#include "Globals.h"
#include "Application.h"
#include "ModuleModel.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "ModuleTexture.h"

#include "GL/glew.h"
#include "Math/float3.h"
#include "Math/float2.h"
#include "MathGeoLib.h"

#include "ModuleCamera.h"

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
    //LoadModel("Models/Triangle/Triangle.gltf");
    return ret;
}

update_status ModuleModel::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleModel::CleanUp()
{
    for (int i = 0; i < meshes.size(); ++i)
    {
        glDeleteVertexArrays(1, &meshes[i]->vao);
        glDeleteBuffers(1, &meshes[i]->vbo);
        glDeleteBuffers(1, &meshes[i]->ebo);
    }

    for (int i = 0; i < meshes.size(); ++i)
    {
        delete meshes[i];
        meshes[i] = nullptr;
    }

    for (int i = 0; i < textures.size(); ++i)
    {
        delete textures[i];
        textures[i] = nullptr;
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
        LOG("[MODEL] Error loading %s: %s", path, error.c_str());
    }

    std::string modelName = path;
    unsigned pos = modelName.find_last_of('/');
    std::string name = modelName.substr(++pos);

    LOG("[MODEL] Starting Loading %s", name.c_str());

    for (const auto& srcMesh : model.meshes)
    {
        for (const auto& primitive : srcMesh.primitives)
        {
            Mesh* mesh = new Mesh();    
            LOG("[MESH] Starting Loading %s", srcMesh.name.c_str());
            mesh->LoadMesh(model, srcMesh, primitive);      
            meshes.push_back(mesh);
            LOG("[MESH] -------------- Finished Loading %s ------------------------", srcMesh.name.c_str());
        }
    }

    if (model.materials.size() > 0)
        LoadMaterials(model, path);

    LOG("[MODEL] -------------- Finished Loading %s ------------------------", name.c_str());
}

void ModuleModel::LoadMaterials(const tinygltf::Model& srcModel, const char* imagePath)
{
    for (const auto& srcMaterial : srcModel.materials)
    {
        unsigned int textureId = 0;
        if (srcMaterial.pbrMetallicRoughness.baseColorTexture.index >= 0)
        {
            const tinygltf::Texture& texture = srcModel.textures[srcMaterial.pbrMetallicRoughness.baseColorTexture.index];
            const tinygltf::Image& image = srcModel.images[texture.source];
            //TODO: Define amb relative paths
            std::string temp = imagePath;
            unsigned cutPos = temp.find_last_of('/');
            temp.erase(++cutPos);
            temp = temp + image.uri.c_str();
            textureId = App->texture->LoadTexture(temp.c_str());
        }
    }
}

void Mesh::LoadVBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
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
        const tinygltf::BufferView& posView = model.bufferViews[posAcc.bufferView];
        const tinygltf::Buffer& posBuffer = model.buffers[posView.buffer];

        numVert = posAcc.count;
        stridePos = posView.byteStride;
        buffSize = 3;

        bufferPos = reinterpret_cast<const float*>(&posBuffer.data[posView.byteOffset + posAcc.byteOffset]);

        LOG("[MESH] Reading gltf Positions");

        AABB aabb;
        aabb.SetFrom(reinterpret_cast<const float3*>(bufferPos), numVert);
        Sphere sphere = aabb.MinimalEnclosingSphere();

        Frustum frustum = App->camera->GetFrustum();

        float3 dir = sphere.Centroid() + float3(sphere.Diameter());

        frustum.pos = dir;

        App->camera->SetFrustumPos(frustum.pos);
        App->camera->LookAt(float3(0.0f));
    }

    if (itTexCoord != primitive.attributes.end())
    {
        const tinygltf::Accessor& texCoordAcc = model.accessors[itTexCoord->second];
        assert(texCoordAcc.type == TINYGLTF_TYPE_VEC2);
        assert(texCoordAcc.componentType == GL_FLOAT);
        const tinygltf::BufferView& texCoordView = model.bufferViews[texCoordAcc.bufferView];
        const tinygltf::Buffer& texCoordBuffer = model.buffers[texCoordView.buffer];

        strideTexCoord = texCoordView.byteStride;
        buffSize += 2;

        bufferTexCoord = reinterpret_cast<const float*>(&texCoordBuffer.data[texCoordView.byteOffset + texCoordAcc.byteOffset]);
        LOG("[MESH] Reading gltf TexCoords");
    }

    if (itNorm != primitive.attributes.end())
    {
        const tinygltf::Accessor& normAcc = model.accessors[itNorm->second];
        assert(normAcc.type == TINYGLTF_TYPE_VEC3);
        assert(normAcc.componentType == GL_FLOAT);
        const tinygltf::BufferView& normView = model.bufferViews[normAcc.bufferView];
        const tinygltf::Buffer& normBuffer = model.buffers[normView.buffer];

        strideNorm = normView.byteStride;
        buffSize += 3;

        bufferNorm = reinterpret_cast<const float*>(&normBuffer.data[normView.byteOffset + normAcc.byteOffset]);
        LOG("[MESH] Reading gltf Normals");
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);   

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffSize * numVert, nullptr, GL_STATIC_DRAW);
    LOG("[MESH] Creating VBO %u, reserved %u memory", vbo, (sizeof(float) * buffSize * numVert));

    float* ptr = (float*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

    //Position(float3) + TexCoords(float2) 
    for (size_t i = 0; i < numVert; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            *(ptr) = *(bufferPos);
            //LOG("Pos %f", *(ptr));
            ++bufferPos;
            ++ptr;
        }
        if (stridePos > 0)     //TODO do something with the bufferSize
            bufferPos += (stridePos/sizeof(float)) - 3; // We Substract 3 because we already had into account the 3 "Position" floats

        if (bufferNorm != nullptr)
        {
            for (int j = 0; j < 3; ++j)
            {
                *(ptr) = *(bufferNorm);
                //LOG("N %f", *(ptr));
                ++bufferNorm;
                ++ptr;
            }
            if (strideNorm > 0)
                bufferNorm += (strideNorm / sizeof(float)) - 3; // We Substract 3 because we already had into account the 3 "Normal" floats
        }

        if (bufferTexCoord != nullptr)
        {
            for (int j = 0; j < 2; ++j)
            {
                *(ptr) = *(bufferTexCoord);
                //LOG("Tc %u %f", i, *(ptr));
                ++bufferTexCoord;
                ++ptr;
            }         
            if (strideTexCoord > 0)
                bufferTexCoord += (strideTexCoord / sizeof(float)) - 2;
        }     
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    LOG("[MESH] Finish VBO map buffer");
}


void Mesh::LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
{
    if (primitive.indices >= 0)
    {
        const tinygltf::Accessor& indAcc = model.accessors[primitive.indices];
        const tinygltf::BufferView& indView = model.bufferViews[indAcc.bufferView];
        const unsigned char* buffer = &(model.buffers[indView.buffer].data[indAcc.byteOffset + indView.byteOffset]);

        numInd = indAcc.count;

        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indAcc.count, nullptr, GL_STATIC_DRAW);
        LOG("[MESH] Creating EBO %u, reserved %u memory", ebo, (sizeof(unsigned int) * indAcc.count));

        unsigned int* ptr = reinterpret_cast<unsigned int*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));

        if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT)
        {
            const uint32_t* bufferInd = reinterpret_cast<const uint32_t*>(buffer);
            for (uint32_t i = 0; i < indAcc.count; ++i)
                ptr[i] = bufferInd[i];
        }
        if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT)
        {
            const uint16_t* bufferInd = reinterpret_cast<const uint16_t*>(buffer);
            for (uint16_t i = 0; i < indAcc.count; ++i)    
                ptr[i] = bufferInd[i];
        }
        if (indAcc.componentType == TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE)
        {
            const uint8_t* bufferInd = reinterpret_cast<const uint8_t*>(buffer);
            for (uint8_t i = 0; i < indAcc.count; ++i)
                ptr[i] = bufferInd[i];
        }

        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        LOG("[MESH] Finish EBO map buffer");
    }
}

void Mesh::CreateVAO()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    LOG("[MESH] Creting VAO %u", vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    //TODO: RECALCULATE OFFSET IF DONT HAVE ATTRIBUTES
    unsigned offset = 0;

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * buffSize, reinterpret_cast<void*>(offset));
    offset += 3;

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * buffSize, reinterpret_cast<void*>((sizeof(float) * offset)));
    if (bufferNorm != nullptr)
        offset += 3;

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * buffSize, reinterpret_cast<void*>((sizeof(float) * offset)));

    glBindVertexArray(0);
}

void Mesh::Draw(const std::vector<Texture*>& textures)
{
    glBindVertexArray(vao);

    glUseProgram(App->program->programId);
    if (!textures.empty() && bufferTexCoord != nullptr)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[App->model->textures.size() - 1]->id);
    }
 
    if(numInd > 0)
        glDrawElements(GL_TRIANGLES, numInd, GL_UNSIGNED_INT, nullptr);
    else
        glDrawArrays(GL_TRIANGLES, 0, numVert);
}

void Mesh::LoadMesh(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive)
{
    if (App->model->textures.size() <= 0)
        disffuseMat = 0;
    else
        disffuseMat = App->model->textures.size();

    LoadVBO(model, mesh, primitive);
    LoadEBO(model, mesh, primitive);

    CreateVAO();
}
