#pragma once
#include "Module.h"

#include "Math/float4x4.h"
#include "Geometry/Frustum.h"

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise() override;

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	unsigned CreateVAO();
	unsigned CreateTriangleVBO();
	unsigned CreateEBO();

	void RenderTriangle();//unsigned vao, unsigned vbo, unsigned ebo);

	void DestroyVAO();
	void DestroyVBO();	
	void DestroyEBO();

	void CreateMatrices(float4x4& model, float4x4& view, float4x4& projection);
	float4x4 LookAtMatrix(float3 pos, float3 forward, float3 up);

private:
	unsigned vao;
	unsigned vbo;
	unsigned ebo;

	Frustum frustum;
	float aspectRatio;

public:
	float4x4 model;
	float4x4 view;
	float4x4 projection;
};

