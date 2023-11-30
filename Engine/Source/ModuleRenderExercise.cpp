#include "GL/glew.h"
#include "MathGeoLib.h"

#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "ModuleModel.h"

#include "DirectXTex.h"


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
        float3(1.0f));

    float vertexData[] = { -1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
                           -1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
                            1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
                            1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f
    };

    unsigned indicesData[] =
    {
        0,1,2,
        2,3,0,
        2,1,0,
        0,3,2
    };

    lightDir = float3(1.0f).Normalized();

    App->model->LoadModel("Models/BakerHouse/BakerHouse.gltf");

    baboon = App->texture->LoadTexture("Textures/Baboon.tga");
    iobamium = App->texture->LoadTexture("Textures/mipmaps.png");
    //
    CreateVAO(vao);
    CreateVBO(vbo);
    CreateEBO(ebo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
    
    glActiveTexture(GL_TEXTURE0);
    
    glBindVertexArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    float4x4 view = App->camera->GetViewMatrix();
    float4x4 projection = App->camera->GetProjectionMatrix();

    glUseProgram(App->program->programId);
    glUniformMatrix4fv(0, 1, GL_TRUE, (GLfloat*)&model);
    glUniformMatrix4fv(1, 1, GL_TRUE, (GLfloat*)&view);
    glUniformMatrix4fv(2, 1, GL_TRUE, (GLfloat*)&projection);

    return ret;
}

update_status ModuleRenderExercise::Update()
{
    glUseProgram(App->program->programId);
    float4x4 view = App->camera->GetViewMatrix();
    float4x4 projection = App->camera->GetProjectionMatrix();
    glUniformMatrix4fv(1, 1, GL_TRUE, (GLfloat*)&view);
    glUniformMatrix4fv(2, 1, GL_TRUE, (GLfloat*)&projection);

    for (int i = 0; i < App->model->meshes.size(); ++i)
    {
        App->model->meshes[i]->Draw(App->model->textures);
    }

    glBindVertexArray(vao);
    
    for (int i = 0; i < 2; ++i)
    {
        if (i == 0)
            glBindTexture(GL_TEXTURE_2D, App->model->textures[App->model->textures.size() - 1]->id);
        else
            glBindTexture(GL_TEXTURE_2D, baboon);
    
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 6 * i));
    }
  
    return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
    bool ret = true;

    DestroyVAO(vao);
    DestroyVBO(vbo);
    DestroyEBO(ebo);
    
    glDeleteTextures(1, (GLuint*) &baboon);
    glDeleteTextures(1, (GLuint*) &iobamium);

    return ret;
}

void ModuleRenderExercise::CreateVAO(unsigned& vao, unsigned num)
{
    glGenVertexArrays(num, &vao);
    glBindVertexArray(vao);
}

void ModuleRenderExercise::CreateVBO(unsigned& vbo, unsigned num)
{
    glGenBuffers(num, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void ModuleRenderExercise::CreateEBO(unsigned& ebo, unsigned num)
{
    glGenBuffers(num, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void ModuleRenderExercise::DestroyVAO(unsigned& vao, unsigned num)
{
    glDeleteVertexArrays(num, &vao);
}

void ModuleRenderExercise::DestroyVBO(unsigned& vbo, unsigned num)
{
    glDeleteBuffers(num, &vbo);
}

void ModuleRenderExercise::DestroyEBO(unsigned& ebo, unsigned num)
{
    glDeleteBuffers(num, &ebo);
}




