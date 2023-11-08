#include "ModuleProgram.h"
#include "GL/glew.h"

#include <windows.h>

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

bool ModuleProgram::Init()
{
    bool ret = true;

    const char* vertexData = LoadShaderSource("Shaders/Vertex.glsl");
    const char* fragmentData = LoadShaderSource("Shaders/Fragment.glsl");

    if (vertexData == nullptr || fragmentData == nullptr)
    {
        LOG("Vertex or Fragment Data are NULL");
    }
    else
    {
        vertexShaderId = CompileShader(GL_VERTEX_SHADER, vertexData);
        fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, fragmentData);

        programId = CreateProgram(vertexShaderId, fragmentShaderId);
    }

    return ret;
}

update_status ModuleProgram::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleProgram::CleanUp()
{
    bool ret = true;

    glDeleteProgram(programId);

    return ret;
}

char* ModuleProgram::LoadShaderSource(const char* shaderFileName)
{
    char* data = nullptr;
    FILE* file = nullptr;

    fopen_s(&file, shaderFileName, "rb");

    if (file)
    {
        fseek(file,0, SEEK_END);
        int size = ftell(file);
        data = (char*)malloc(size + 1);
        fseek(file, 0, SEEK_SET);
        fread(data, 1, size, file);
        data[size] = 0;      
        fclose(file);
    }

    LOG("Loaded %s:", shaderFileName);

    return data;
}

unsigned int ModuleProgram::CompileShader(unsigned shaderType, const char* shaderData)
{
    unsigned shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &shaderData, NULL);
    glCompileShader(shaderId);

    int res = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &res);

    if (res == GL_FALSE)
    {
        int len = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &len);
        if (len > 0)
        {
            int written = 0;
            char* info = (char*)malloc(len);
            glGetShaderInfoLog(shaderId, len, &written, info);
            LOG("Log Info: %s", info);
            free(info);
        }
    }

    LOG("Compiled Shader %u", shaderId);

    return shaderId;
}

unsigned ModuleProgram::CreateProgram(unsigned vertexShader, unsigned fragmentShader)
{
    unsigned programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);
    int res;
    glGetProgramiv(programId, GL_LINK_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &len);
        if (len > 0)
        {
            int written = 0;
            char* info = (char*)malloc(len);
            glGetProgramInfoLog(programId, len, &written, info);
            LOG("Program Log Info: %s", info);
            free(info);
        }
    }

    LOG("Created Shader Program %u", programId);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return programId;
}
