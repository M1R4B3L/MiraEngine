#include "GL/glew.h"
#include "MathGeoLib.h"

#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "ModuleCamera.h"


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

    projection = App->camera->GetProjectionMatrix();
    view = App->camera->GetViewMatrix();

    //
    CreateVAO();
    CreateTriangleVBO();
    CreateEBO();
     
    return ret;
}

update_status ModuleRenderExercise::Update()
{
    RenderTriangle();// vao, vbo, ebo);
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

unsigned ModuleRenderExercise::CreateVAO()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return vao;
}

unsigned ModuleRenderExercise::CreateTriangleVBO()
{
    float vertexData[] = { -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
                            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
                            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
                            0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glUseProgram(App->program->programId);
    glUniformMatrix4fv(0, 1, GL_TRUE, (GLfloat*)&model);
    glUniformMatrix4fv(1, 1, GL_TRUE, (GLfloat*)&view);
    glUniformMatrix4fv(2, 1, GL_TRUE, (GLfloat*)&projection);

    return vbo;
}

unsigned ModuleRenderExercise::CreateEBO()
{
    bool ret = true;

    unsigned indicesData[] = { 0,1,2, 
                               2,3,0
    };

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    return ret;
}

void ModuleRenderExercise::RenderTriangle()//unsigned vao, unsigned vbo, unsigned ebo)
{
    glUseProgram(App->program->programId);

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




