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
	unsigned CreateTexture(const char* path);

	void CreateVAO(unsigned& vao, unsigned num = 1);
	void CreateVBO(unsigned& vbo, unsigned num = 1);
	void CreateEBO(unsigned& ebo, unsigned num = 1);

	void DestroyVAO(unsigned& vao, unsigned num = 1);
	void DestroyVBO(unsigned& vbo, unsigned num = 1);
	void DestroyEBO(unsigned& ebo, unsigned num = 1);

private:
	unsigned vao;
	unsigned vbo;
	unsigned ebo;

	unsigned baboon;
	unsigned iobamium;

public:
	float4x4 model;

};

