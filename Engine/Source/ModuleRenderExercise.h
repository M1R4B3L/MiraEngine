#pragma once
#include "Module.h"
class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

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
};

