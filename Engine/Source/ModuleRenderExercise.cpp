#include "GL/glew.h"
#include "MathGeoLib.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"



ModuleRenderExercise::ModuleRenderExercise()
{
    
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Init()
{
    bool ret = true;

    CreateMatrices(model, view, projection);

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

void ModuleRenderExercise::CreateMatrices(math::float4x4& model, math::float4x4& view, math::float4x4& projection)
{
    aspectRatio = (float) App->window->GetWidth() / (float) App->window->GetHeight();

    frustum.type = FrustumType::PerspectiveFrustum;
    frustum.pos = float3(0.0f, 0.0f, 2.0f);
    frustum.front = -float3::unitZ;
    frustum.up = float3::unitY;

    frustum.nearPlaneDistance = 0.1f;
    frustum.farPlaneDistance = 100.0f;
    frustum.verticalFov = math::pi / 4.0f;
    frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);

    projection = frustum.ProjectionMatrix();
    model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f),
                              float4x4::RotateZ(0.0f),
                              float3(1.0f, 1.0f, 1.0f));

    view = LookAtMatrix(frustum.pos, frustum.front, frustum.up);
}

unsigned ModuleRenderExercise::CreateVAO()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return vao;
}

unsigned ModuleRenderExercise::CreateTriangleVBO()
{
    float vertexData[] = { -0.5f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 
                            -0.5f, -0.5f, -1.0f, 0.0f, 1.0f, 0.0f,
                            0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f,
                            0.5f, 0.5f, -1.0f, 0.0f, 1.0f, 0.0f
    };
    
    glUseProgram(App->program->programId);
    glUniformMatrix4fv(0, 1, GL_TRUE, (GLfloat*) &model);
    glUniformMatrix4fv(1, 1, GL_TRUE, (GLfloat*) &view);
    glUniformMatrix4fv(2, 1, GL_TRUE, (GLfloat*) &projection);

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

float4x4 ModuleRenderExercise::LookAtMatrix(float3 pos, float3 forward, float3 up)
{
    forward.Normalized();
    float3 right = (forward.Cross(up)).Normalized();  
    up = (right.Cross(forward)).Normalized();

    float4x4 matrix = {right.x,     right.y,    right.z,    -(pos.Dot(right)),
                       up.x,        up.y,       up.z,       -(pos.Dot(up)),
                       -forward.x,  -forward.y, -forward.z,  (pos.Dot(forward)),
                           0,         0,           0,          1};

    return matrix;
}





