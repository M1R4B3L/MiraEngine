#pragma once
#include "Module.h"

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

	void SetPlaneDistances();

	void SetNearPlanePos();
	void SetFarPlanePos();

	void LookAt(float3 pos);

	float4x4 GetProjectionMatrix() const;
	float4x4 GetViewMatrix() const; 
	float4x4 LookAtMatrix(float3 pos, float3 forward, float3 up);

	void RecalculateMatrices(float3 newPos, float4x4& proj, float4x4& view) ;

	void Move();

public:
	Frustum frustum;
	float aspectRatio;

private:
	float4x4 view;
	float4x4 projection;

	float cameraSpeed = 2.0f;
};

