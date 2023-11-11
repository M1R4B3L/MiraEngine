#include "GL/glew.h"
#include "MathGeoLib.h"

#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"


ModuleRenderExercise::ModuleRenderExercise()
{
    
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
    bool ret = true;

    model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f),
        float4x4::RotateZ(0.0f),
        float3(1.0f, 1.0f, 1.0f));

    baboon = CreateTexture();
    //
    CreateVAO();
    CreateTriangleVBO();
    CreateEBO();
     
    return ret;
}

update_status ModuleRenderExercise::Update()
{
    RenderTriangle();

    return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
    bool ret = true;

    DestroyVAO();
    DestroyVBO();
    DestroyEBO();

    return ret;
}

unsigned ModuleRenderExercise::CreateTexture()
{
    unsigned texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int format;
    int internalFormat;
    GLenum type;
    switch (App->texture->baboon.GetMetadata().format)
    {
    case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
    case DXGI_FORMAT_R8G8B8A8_UNORM:
        internalFormat = GL_RGBA8;
        format = GL_RGBA;
        type = GL_UNSIGNED_BYTE;
        break;
    case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
    case DXGI_FORMAT_B8G8R8A8_UNORM:
        internalFormat = GL_RGBA8;
        format = GL_BGRA;
        type = GL_UNSIGNED_BYTE;
        break;
    case DXGI_FORMAT_B5G6R5_UNORM:
        internalFormat = GL_RGB8;
        format = GL_BGR;
        type = GL_UNSIGNED_BYTE;
        break;
    default:
        assert(false && "Unsupported format");
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, App->texture->baboon.GetMetadata().mipLevels - 1);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, App->texture->baboon.GetMetadata().width, App->texture->baboon.GetMetadata().height, 0, format, type, App->texture->baboon.GetPixels());

    //TODO Handle if Texture has mipmaps
    if ((App->texture->baboon.GetMetadata().mipLevels > 0) - 1)
    {
        for (size_t i = 0; i < App->texture->baboon.GetMetadata().mipLevels; ++i)
        {
            const DirectX::Image* mip = App->texture->baboon.GetImage(i, 0, 0);
            glTexImage2D(GL_TEXTURE_2D, i, internalFormat, mip->width, mip->height, 0, format, type, mip->pixels);
        }
    }
    else
        glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

void ModuleRenderExercise::CreateVAO()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void ModuleRenderExercise::CreateTriangleVBO()
{
    float vertexData[] = { -5.5f,  5.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
                           -5.5f, -5.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
                            5.5f, -5.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
                            5.5f,  5.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    float4x4 view = App->camera->GetViewMatrix();
    float4x4 projection = App->camera->GetProjectionMatrix();

    glUseProgram(App->program->programId);
    glUniformMatrix4fv(0, 1, GL_TRUE, (GLfloat*)&model);
    glUniformMatrix4fv(1, 1, GL_TRUE, (GLfloat*)&view);
    glUniformMatrix4fv(2, 1, GL_TRUE, (GLfloat*)&projection);

}

void ModuleRenderExercise::CreateEBO()
{
    unsigned indicesData[] = { 0,1,2, 
                               2,3,0
    };

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, baboon);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void ModuleRenderExercise::RenderTriangle()//unsigned vao, unsigned vbo, unsigned ebo)
{
    glUseProgram(App->program->programId);
    float4x4 view = App->camera->GetViewMatrix();
    float4x4 projection = App->camera->GetProjectionMatrix();
    glUniformMatrix4fv(1, 1, GL_TRUE, (GLfloat*)&view);
    glUniformMatrix4fv(2, 1, GL_TRUE, (GLfloat*)&projection);

    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void ModuleRenderExercise::DestroyVAO()
{
    glDeleteBuffers(1, &vao);
}

void ModuleRenderExercise::DestroyVBO()
{
    glDeleteBuffers(1, &vbo);
}

void ModuleRenderExercise::DestroyEBO()
{
    glDeleteBuffers(1, &ebo);
}




