#define _CRT_SECURE_NO_WARNINGS

#include "ModuleTexture.h"

#include "DirectXTex.h"
#include <cstdlib>

ModuleTexture::ModuleTexture()
{
}

ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Init()
{
    bool ret = true;

    return ret;
}

bool ModuleTexture::CleanUp()
{
    return true;
}

DirectX::ScratchImage ModuleTexture::LoadTexture(const char* path)
{
    size_t size = strlen(path) + 1;
    wchar_t* portName = new wchar_t[size];
    size_t outSize;
    mbstowcs_s(&outSize, portName, size, path, size - 1);

    long err;
    long err2;
    long err3;

    DirectX::ScratchImage newImage; 

    err = DirectX::LoadFromDDSFile(portName, DirectX::DDS_FLAGS_NONE, nullptr, newImage);
    if (FAILED(err))
    {
        LOG("Failed DDS Don't know why");
    }
    else
    {
        LOG("Succes Loading DDS image");
        return newImage;
    }
    err2 = DirectX::LoadFromTGAFile(portName, DirectX::TGA_FLAGS_NONE, nullptr, newImage);
    if (FAILED(err2))
    {
        LOG("Failed TGA Don't know why");
    }
    else
    {
        LOG("Succes Loading TGA image");
        return newImage;
    }
    err3 = DirectX::LoadFromWICFile(portName, DirectX::WIC_FLAGS_NONE, nullptr, newImage);
    if (FAILED(err3))
    {
        LOG("Failed ALL Don't know why");
    }
    else
    {
        LOG("Succes Loading WIC image");
        return newImage;
    }
   
}
