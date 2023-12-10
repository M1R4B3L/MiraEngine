#pragma once

#include "Module.h"

#include "Math/float2.h"
#include "Math/float4x4.h"
#include "Geometry/Frustum.h"

class ModuleCamera : public Module
{
public:

	ModuleCamera();
	~ModuleCamera();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	const float4x4 GetProjectionMatrix() const;
	const float4x4 GetViewMatrix() const;
	const Frustum GetFrustum() const;
	const float GetCameraSpeed() const;

	void SetFrustumPos(const float3& pos);

	void SetFOV(float newFOV);
	void SetAspectRatio(float newAspectRatio);

	void SetPlaneDistances(float near, float far);

	void SetNearPlanePos(float near);
	void SetFarPlanePos(float far);

	void SetCameraSpeed(float speed);

	void LookAt(const float3& pos);

	float4x4 CameraMatrix(float3 pos, float3 forward, float3 up) const;

	void Zoom();
	void Orbit();

	void Translate(const float3& axis, const float& speed);
	void Rotate(const float3& axis, const float& angle);
	//Center to 0,0,0 / Focus to GameObject / Move Camera to accept model Size  arctang(vfov/2 / maxAABB height point)/ Camera Speed

public:


private:
	Frustum frustum;
	float aspectRatio;

	float cameraSpeed;	
	
	float2 lastMousePos;
};

