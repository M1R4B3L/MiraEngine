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

    return ret;
}

update_status ModuleRenderExercise::Update()
{
    RenderVBO(vbo);

    return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
    bool ret = true;

    DestroyVBO();

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
    float vertexData[] = { -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
                            1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    return vbo;
}

void ModuleRenderExercise::DestroyVBO()
{
    glDeleteBuffers(1, &vbo);
}

void ModuleRenderExercise::RenderVBO(unsigned vbo)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    //TODO: Accept color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*6, (void*) (sizeof(float)*3));

    glUseProgram(App->GetProgram()->programId);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}



