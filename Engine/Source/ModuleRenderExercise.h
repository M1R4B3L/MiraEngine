#pragma once
#include "Module.h"

#include "Math/float4x4.h"

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

private:
	unsigned vao;
	unsigned vbo;
	unsigned ebo;

public:
	float4x4 model;
	float4x4 view;
	float4x4 projection;
};

