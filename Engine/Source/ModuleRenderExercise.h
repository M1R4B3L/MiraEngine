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
	unsigned int CreateVAO();

	unsigned int CreateTriangleVBO();
	void DestroyVBO();
	void RenderVBO(unsigned vbo);


private:
	unsigned int vao;
	unsigned int vbo;
};

