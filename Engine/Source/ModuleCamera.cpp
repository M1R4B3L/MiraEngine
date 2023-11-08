#include "Application.h"
#include "ModuleWindow.h"
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

    return ret;
}

update_status ModuleCamera::Update()
{

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
