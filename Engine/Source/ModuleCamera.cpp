#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleCamera.h"

#include "MathGeoLib.h"

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
    bool ret = true;

    aspectRatio = (float)App->window->GetWidth() / (float)App->window->GetHeight();

    frustum.type = FrustumType::PerspectiveFrustum;
    frustum.pos = float3(0.0f, 1.0f, 15.0f);
    frustum.front = -float3::unitZ;
    frustum.up = float3::unitY;

    frustum.nearPlaneDistance = 0.1f;
    frustum.farPlaneDistance = 100.0f;
    frustum.verticalFov = math::pi / 4.0f;
    frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);

    projection = frustum.ProjectionMatrix();
    view = LookAtMatrix(frustum.pos, frustum.front, frustum.up);

    oldPos.x = SCREEN_WIDTH / 2.0f;
    oldPos.y = SCREEN_HEIGHT / 2.0f;

    return ret;
}

update_status ModuleCamera::Update()
{
    Move();
    PanCamera();
    Rotate();

    return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
    return false;
}

float4x4 ModuleCamera::GetProjectionMatrix() const
{
    return projection;
}

float4x4 ModuleCamera::GetViewMatrix() const
{
    return view;
}

float4x4 ModuleCamera::LookAtMatrix(float3 pos, float3 forward, float3 up)
{
    forward.Normalized();
    float3 right = (forward.Cross(up)).Normalized();
    up = (right.Cross(forward)).Normalized();

    float4x4 matrix = { right.x,     right.y,    right.z,    -(pos.Dot(right)),
                       up.x,        up.y,       up.z,       -(pos.Dot(up)),
                       -forward.x,  -forward.y, -forward.z,  (pos.Dot(forward)),
                           0,         0,           0,          1 };

    return matrix;
}

void ModuleCamera::RecalculateMatrices(float3 newPos, float4x4& proj, float4x4& view)
{
    projection = frustum.ProjectionMatrix();
    view = LookAtMatrix(frustum.pos, frustum.front, frustum.up);
}

void ModuleCamera::Rotate()
{
    int dx = -App->input->mouseMotion.x;
    int dy = -App->input->mouseMotion.y;

    float sens = 1.0f * 0.002f;
    if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_REPEAT)
    {
        if (dx != 0)
        {
            float deltaX = (float)dx * sens;

            Quat q = Quat::RotateY(deltaX);

            frustum.front = q.Mul(frustum.front).Normalized();
            frustum.up = q.Mul(frustum.up).Normalized();
            

            /*X = rotate(X, DeltaX, vec3(0.0f, 1.0f, 0.0f));
            Y = rotate(Y, DeltaX, vec3(0.0f, 1.0f, 0.0f));
            Z = rotate(Z, DeltaX, vec3(0.0f, 1.0f, 0.0f));*/
        }

        if (dy != 0)
        {
           /* float DeltaY = (float)dy * sens;

            Quat q = Quat::RotateAxisAngle(frustum.WorldRight(), DeltaY);

            float3 vecY = q.Mul(frustum.up.Normalized());

            if (vecY.y > 0.0f)
            {
                frustum.up = vecY;
                frustum.front = q.Mul(frustum.front).Normalized();
            }*/
        }

        view = LookAtMatrix(frustum.pos, frustum.front, frustum.up);
        RecalculateMatrices(frustum.pos, projection, view);
    }
}

void ModuleCamera::PanCamera()
{
    float3 newPos = float3::zero;
    float3 x_pos = float3::zero;
    float3 y_pos = float3::zero;

    float speed = 2.0f * 0.001f;

    if (App->input->GetMouseButtonDown(SDL_BUTTON_MIDDLE) == KeyState::KEY_REPEAT)
    {

        if (App->input->mouseMotion.x != 0)
        {
            x_pos = -App->input->mouseMotion.x * frustum.WorldRight() * speed;
        }

        if (App->input->mouseMotion.y != 0)
        {
            y_pos = App->input->mouseMotion.y * frustum.up * speed;
        }
    }
  
    newPos = x_pos + y_pos;

    frustum.pos = frustum.pos + newPos;

    RecalculateMatrices(frustum.pos, projection, view);
}

void ModuleCamera::Move()
{
    float deltaTime = 0.02;

    if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT)
    {
        frustum.pos = frustum.pos + (frustum.front * (cameraSpeed * deltaTime));
    }
    if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT)
    {
        frustum.pos = frustum.pos - (frustum.front * (cameraSpeed * deltaTime));
    }
    if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT)
    {
        frustum.pos = frustum.pos + (frustum.WorldRight() * (cameraSpeed * deltaTime));
    }
    if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT)
    {
        frustum.pos = frustum.pos - (frustum.WorldRight() * (cameraSpeed * deltaTime));
    }
    //LOG("%f", frustum.pos.x);
    //LOG("%f", frustum.pos.y);
    //LOG("%f", frustum.pos.z);
    
    if (App->input->GetKey(SDL_SCANCODE_Q) == KeyState::KEY_REPEAT)
    {
        frustum.pos.y = frustum.pos.y - (cameraSpeed * deltaTime);
    }
    if (App->input->GetKey(SDL_SCANCODE_E) == KeyState::KEY_REPEAT)
    {
        frustum.pos.y = frustum.pos.y + (cameraSpeed * deltaTime);
    }
    
    RecalculateMatrices(frustum.pos, projection, view);
    
  
}
