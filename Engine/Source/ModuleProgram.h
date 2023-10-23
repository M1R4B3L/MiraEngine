#pragma once
#include "Module.h"
class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	unsigned int CompileShader(unsigned int shaderType, const char* shaderSource);
};

