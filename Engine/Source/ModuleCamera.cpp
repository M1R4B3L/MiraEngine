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

    cameraSpeed = 0.5f;

    float2 winSize = App->window->GetWindowSize();
    aspectRatio = winSize.x / winSize.y;

    frustum.type = FrustumType::PerspectiveFrustum;
    frustum.pos = float3(0.0f, 1.0f, 15.0f);
    frustum.front = -float3::unitZ;
    frustum.up = float3::unitY;

    frustum.nearPlaneDistance = 0.1f;
    frustum.farPlaneDistance = 10000.0f;
    frustum.verticalFov = math::pi / 4.0f;
    frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * aspectRatio);

    LookAt(float3(0.0f));

    lastMousePos.x = SCREEN_WIDTH / 2;
    lastMousePos.y = SCREEN_HEIGHT / 2;

    return ret;
}

update_status ModuleCamera::Update()
{
    //TODO: ADD MORE SPEED VARIABLES
    float2 motion = App->input->GetMouseMotion();

    if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_REPEAT)
    {
        if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT)
        {
            Translate(frustum.front, cameraSpeed * 0.02);
        }
        if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT)
        {
            Translate(-frustum.front, cameraSpeed * 0.02);
        }
        if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT)
        {
            Translate(-frustum.WorldRight(), cameraSpeed * 0.02);
        }
        if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT)
        {
            Translate(frustum.WorldRight(), cameraSpeed * 0.02);
        }
        if (App->input->GetKey(SDL_SCANCODE_Q) == KeyState::KEY_REPEAT)
        {
            Translate(-frustum.up, cameraSpeed * 0.02);
        }
        if (App->input->GetKey(SDL_SCANCODE_E) == KeyState::KEY_REPEAT)
        {
            Translate(frustum.up, cameraSpeed * 0.02);
        }

        if (motion.x != 0)
        {
            Rotate(float3::unitY, ((lastMousePos.x - App->input->GetMousePos().x) * cameraSpeed * 0.2));
        }
        if (motion.y != 0)
        {
            Rotate(frustum.WorldRight(), ((lastMousePos.y - App->input->GetMousePos().y) * cameraSpeed * 0.2));
        }
    }

    if (App->input->GetMouseButtonDown(SDL_BUTTON_MIDDLE) == KeyState::KEY_REPEAT)
    {
        if(motion.x != 0)
            Translate(-(motion.x * frustum.WorldRight()), cameraSpeed * 0.02);
        if (motion.y != 0)
            Translate((motion.y * frustum.up), cameraSpeed * 0.02);
    }

    Zoom();

    if (((App->input->GetKey(SDL_SCANCODE_LALT) == KeyState::KEY_REPEAT)) && (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT))
    {
        
    }

    lastMousePos = App->input->GetMousePos();

    return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
    return false;
}

const float4x4 ModuleCamera::GetProjectionMatrix() const
{
    return frustum.ProjectionMatrix();
}

const float4x4 ModuleCamera::GetViewMatrix() const
{
    return frustum.ViewMatrix();
}

const Frustum ModuleCamera::GetFrustum() const
{
    return frustum;
}

void ModuleCamera::SetFrustumPos(const float3& pos)
{
    frustum.pos = pos;
}

void ModuleCamera::SetFOV(float angle)
{
    frustum.horizontalFov = math::DegToRad(angle);
    frustum.verticalFov = 2.f * atanf(tanf(frustum.horizontalFov * 0.5f) * (1.0f / aspectRatio));
}

void ModuleCamera::SetAspectRatio(float newAspectRatio)
{
    aspectRatio = newAspectRatio;
    frustum.verticalFov = 2.f * atanf(tanf(frustum.horizontalFov * 0.5f) * (1.0f / aspectRatio));
}

void ModuleCamera::SetPlaneDistances(float nearDist, float farDist)
{
    frustum.nearPlaneDistance = nearDist;
    frustum.farPlaneDistance = farDist;
}

void ModuleCamera::SetNearPlanePos(float nearPos)
{
    frustum.nearPlaneDistance = nearPos;
}

void ModuleCamera::SetFarPlanePos(float farPos)
{
    frustum.farPlaneDistance = farPos;
}

void ModuleCamera::LookAt(const float3& pos)
{
    float3 dir = float3(pos - frustum.pos).Normalized();

    //TODO DO CUSTOM LOOK AT FUNCTION (CHANGE CAMERA MATRIX FUNCTION)
    float3x3 lookAtMatrix = float3x3::LookAt(frustum.front, dir, frustum.up, float3::unitY);
    frustum.front = lookAtMatrix.MulDir(frustum.front).Normalized();
    frustum.up = lookAtMatrix.MulDir(frustum.up).Normalized();
}

float4x4 ModuleCamera::CameraMatrix(float3 pos, float3 target, float3 up) const
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

void ModuleCamera::Zoom()
{
    float wheelY = App->input->GetWheelScrollY();
    float deltaTime = 0.9;

    if (wheelY > 0)
    {
        Translate(frustum.front, cameraSpeed * deltaTime);
    }
    if (wheelY < 0)
    {
        Translate(-frustum.front, cameraSpeed * deltaTime);
    }
}

void ModuleCamera::Orbit()
{
}

void ModuleCamera::Translate(const float3& axis, const float& speed)
{
    frustum.pos += axis * cameraSpeed;
}

void ModuleCamera::Rotate(const float3& axis, const float& angle)
{
    float3x3 rotationMatrix = float3x3::RotateAxisAngle(axis,math::DegToRad(angle));
    frustum.front = rotationMatrix.MulDir(frustum.front.Normalized()).Normalized();
    frustum.up = rotationMatrix.MulDir(frustum.up.Normalized()).Normalized();
}
