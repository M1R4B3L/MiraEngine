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
	unsigned CreateTexture();

	void CreateVAO();
	void CreateTriangleVBO();
	void CreateEBO();

	void RenderTriangle();//unsigned vao, unsigned vbo, unsigned ebo);

	void DestroyVAO();
	void DestroyVBO();	
	void DestroyEBO();

private:
	unsigned vao;
	unsigned vbo;
	unsigned ebo;

	unsigned baboon;

public:
	float4x4 model;

};

