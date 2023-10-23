#include "ModuleProgram.h"

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

bool ModuleProgram::Init()
{
    bool ret = true;
    return ret;
}

update_status ModuleProgram::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleProgram::CleanUp()
{
    bool ret = true;
    return ret;
}

unsigned int ModuleProgram::CompileShader(unsigned int shaderType, const char* shaderSource)
{
    return 0;
}
