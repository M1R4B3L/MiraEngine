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

    lightDir = float3(1.0f).Normalized();

    App->model->LoadModel("Models/Fox/fox.gltf");

    float4x4 view = App->camera->GetViewMatrix();
    float4x4 projection = App->camera->GetProjectionMatrix();

    glUseProgram(App->program->programId);
    glUniformMatrix4fv(0, 1, GL_TRUE, static_cast<GLfloat*>(&model[0][0]));
    glUniformMatrix4fv(1, 1, GL_TRUE, static_cast<GLfloat*>(&view[0][0]));
    glUniformMatrix4fv(2, 1, GL_TRUE, static_cast<GLfloat*>(&projection[0][0]));

    return ret;
}

update_status ModuleRenderExercise::Update()
{
    glUseProgram(App->program->programId);
    float4x4 view = App->camera->GetViewMatrix();
    float4x4 projection = App->camera->GetProjectionMatrix();
    glUniformMatrix4fv(1, 1, GL_TRUE, static_cast<GLfloat*>(&view[0][0]));
    glUniformMatrix4fv(2, 1, GL_TRUE, static_cast<GLfloat*>(&projection[0][0]));

    for (int i = 0; i < App->model->meshes.size(); ++i)
    {
        App->model->meshes[i]->Draw(App->model->textures);
    }

    return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
    bool ret = true;

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




