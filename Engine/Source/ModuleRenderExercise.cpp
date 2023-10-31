#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "GL/glew.h"

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
    bool ret = true;

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

    return ret;
}

void ModuleRenderExercise::RenderTriangle()//unsigned vao, unsigned vbo, unsigned ebo)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glUseProgram(App->program->programId);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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




