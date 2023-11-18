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
    view = LookAtMatrix(frustum.pos, float3(0.0f), frustum.up).Inverted();

    lastMousePos.x = SCREEN_WIDTH / 2;
    lastMousePos.y = SCREEN_HEIGHT / 2;

    yaw = -90;
    pitch = 0;

    return ret;
}

update_status ModuleCamera::Update()
{
    Move();
    PanCamera();
    Rotate();

    view = LookAtMatrix(frustum.pos, frustum.pos + frustum.front, frustum.up).Inverted();

    return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
    return false;
}

void ModuleCamera::SetFOV(float angle)
{
    frustum.horizontalFov = angle;
    frustum.verticalFov = 2.f * atanf(tanf(frustum.horizontalFov * 0.5f) * aspectRatio);
    
    projection = frustum.ProjectionMatrix();
}

void ModuleCamera::SetAspectRatio(float newAspectRatio)
{
}

float4x4 ModuleCamera::GetProjectionMatrix() const
{
    return projection;
}

float4x4 ModuleCamera::GetViewMatrix() const
{
    return view;
}

float4x4 ModuleCamera::LookAtMatrix(float3 pos, float3 target, float3 up)
{
    float3 forward = (target - pos).Normalized();
    float3 right = forward.Cross(up).Normalized();
    up = right.Cross(forward).Normalized();

    float4x4 cameraMatrix = {

        right.x, up.x, -forward.x,  pos.x,
        right.y, up.y, -forward.y,  pos.y,
        right.z, up.z, -forward.z,  pos.z,
            0,    0,        0,        1
    };

    return cameraMatrix;
}

void ModuleCamera::UpdateFrustumVectors()
{
    frustum.front.x = math::Cos(math::DegToRad(yaw)) * math::Cos(math::DegToRad(pitch));
    frustum.front.y = math::Sin(math::DegToRad(pitch));
    frustum.front.z = math::Sin(math::DegToRad(yaw)) * math::Cos(math::DegToRad(pitch));

    frustum.front = frustum.front.Normalized();
    frustum.WorldRight() = frustum.front.Cross(float3::unitY).Normalized(); 
    frustum.up = frustum.WorldRight().Cross(frustum.front).Normalized();
}


void ModuleCamera::Rotate()
{
    int dx = -App->input->mouseMotion.x;
    int dy = -App->input->mouseMotion.y;
    float sens = 10.0f * 0.02f;

    if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_REPEAT)
    {
        if (dx != 0)
        {       
            //float deltaX = App->input->mousePos.x - lastMousePos.x;
            //float3x3 rotationDeltaMatrix = float3x3::RotateY(math::DegToRad(-(deltaX * sens))); // = some rotation delta value
            //
            //float3 oldFront = frustum.front.Normalized();
            //frustum.front = rotationDeltaMatrix.MulDir(oldFront);
            //float3 oldUp = frustum.up.Normalized();
            //frustum.up = rotationDeltaMatrix.MulDir(oldUp);

            float deltaX = App->input->mousePos.x - lastMousePos.x;
            deltaX *= sens;
            yaw += deltaX;

        }
        if (dy != 0)
        {
            float deltaY = lastMousePos.y - App->input->mousePos.y;
            deltaY *= sens;
            pitch += deltaY;
            
        }

        UpdateFrustumVectors();

        view = LookAtMatrix(frustum.pos, frustum.front.Normalized(), frustum.up.Normalized()).Inverted();
    }

    lastMousePos.x = App->input->mousePos.x;
    lastMousePos.y = App->input->mousePos.y;
}

void ModuleCamera::PanCamera()
{
    float3 newPos = float3::zero;
    float3 x_pos = float3::zero;
    float3 y_pos = float3::zero;
    
    float speed = 2.0f * 0.02f;
    
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
}

void ModuleCamera::Move()
{
    float deltaTime = 0.02;

    float3 cameraPos = frustum.pos;

    if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT)
    {
        cameraPos += frustum.front * (cameraSpeed * deltaTime);
    }
    if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT)
    {
        cameraPos -= frustum.front * (cameraSpeed * deltaTime);
    }

    if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT)
    {
        cameraPos += frustum.WorldRight() * (cameraSpeed * deltaTime);
    }
    if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT)
    {
        cameraPos -= frustum.WorldRight() * (cameraSpeed * deltaTime);
    }

    if (App->input->GetKey(SDL_SCANCODE_Q) == KeyState::KEY_REPEAT)
    {
        cameraPos -= frustum.up * (cameraSpeed * deltaTime);
    }
    if (App->input->GetKey(SDL_SCANCODE_E) == KeyState::KEY_REPEAT)
    {
        cameraPos += frustum.up * (cameraSpeed * deltaTime);
    }

    frustum.pos = cameraPos;
}
