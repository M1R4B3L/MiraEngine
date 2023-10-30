#pragma once
#include "Module.h"
class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram() override;

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	char* LoadShaderSource(const char* shaderFileName);
	unsigned CompileShader(unsigned shaderType, const char* shaderSource);
	unsigned CreateProgram(unsigned vertexShader, unsigned fragmentShader);

public:
	unsigned programId;

private:
	unsigned vertexShaderId;
	unsigned fragmentShaderId;
};

