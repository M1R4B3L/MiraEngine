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

	const char* LoadShaderSource(const char* shaderFileName) const;
	const unsigned CompileShader(unsigned shaderType, const char* shaderSource) const;
	const unsigned CreateProgram(unsigned vertexShader, unsigned fragmentShader) const;

public:
	unsigned programId;

private:
	unsigned vertexShaderId;
	unsigned fragmentShaderId;
};

