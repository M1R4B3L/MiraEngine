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

	void SetFOV(float newFOV);
	void SetAspectRatio(float newAspectRatio);

	void SetPlaneDistances(float near, float far);

	void SetNearPlanePos(float near);
	void SetFarPlanePos(float far);

	void LookAt(float3 pos);

	float4x4 GetProjectionMatrix() const;
	float4x4 GetViewMatrix() const; 

	float4x4 LookAtMatrix(float3 pos, float3 forward, float3 up);

	void Rotate();
	void PanCamera();
	void Move();
	void Zoom();

public:
	Frustum frustum;
	float aspectRatio;

private:
	float4x4 view;
	float4x4 projection;

	float cameraSpeed = 2.0f;	
	
	float2 lastMousePos;
};

