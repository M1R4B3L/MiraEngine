#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleModel.h"

#include "GL/glew.h"
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

unsigned ModuleTexture::LoadTexture(const char* path)
{
    size_t size = strlen(path) + 1;
    wchar_t* portName = new wchar_t[size];
    size_t outSize;
    mbstowcs_s(&outSize, portName, size, path, size - 1);

    long err;
    DirectX::ScratchImage newImage; 

    err = DirectX::LoadFromDDSFile(portName, DirectX::DDS_FLAGS_NONE, nullptr, newImage);
    if (SUCCEEDED(err))
    {
        LOG("[TEXTURE] Loading DDS image %s", path);
    }
    else
    {
        LOG("[TEXTURE] Fail unable to load DDS image %s", path);

        err = DirectX::LoadFromTGAFile(portName, DirectX::TGA_FLAGS_NONE, nullptr, newImage);
        if (SUCCEEDED(err))
        {
            LOG("[TEXTURE] Loading TGA image %s", path);
        }
        else
        {
            LOG("[TEXTURE] Fail unable to load TGA image %s", path);

            err = DirectX::LoadFromWICFile(portName, DirectX::WIC_FLAGS_NONE, nullptr, newImage);
            if (SUCCEEDED(err))
            {
                LOG("[TEXTURE] Loading WIC image %s", path);
            }
            else
            {
                LOG("[TEXTURE] Fail unable to load WIC image %s", path);
            }
        }
    }

    Texture* texture = new Texture;

    texture->pixels = newImage.GetPixels();
    
    //TODO: Need a way to compare 2 textures to skip already loaded textures

    if (texture->pixels != nullptr)
    {
        glGenTextures(1, &texture->id);
        glBindTexture(GL_TEXTURE_2D, texture->id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int format;
        int internalFormat;
        GLenum type;

        switch (newImage.GetMetadata().format)
        {
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            internalFormat = GL_RGBA8;
            format = GL_RGBA;
            type = GL_UNSIGNED_BYTE;
            break;
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
        case DXGI_FORMAT_B8G8R8A8_UNORM:
            internalFormat = GL_RGBA8;
            format = GL_BGRA;
            type = GL_UNSIGNED_BYTE;
            break;
        case DXGI_FORMAT_B5G6R5_UNORM:
            internalFormat = GL_RGB8;
            format = GL_BGR;
            type = GL_UNSIGNED_BYTE;
            break;
        default:
            assert(false && "Unsupported format");
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, newImage.GetMetadata().mipLevels - 1);

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, newImage.GetMetadata().width, newImage.GetMetadata().height, 0, format, type, newImage.GetPixels());

        //TODO Handle if Texture has mipmaps
        if ((newImage.GetMetadata().mipLevels > 1))
        {
            for (size_t i = 1; i < newImage.GetMetadata().mipLevels; ++i)
            {
                const DirectX::Image* mip = newImage.GetImage(i, 0, 0);
                glTexImage2D(GL_TEXTURE_2D, i, internalFormat, mip->width, mip->height, 0, format, type, mip->pixels);
            }
        }
        else
            glGenerateMipmap(GL_TEXTURE_2D);

        App->model->textures.push_back(texture);
        return texture->id;
    }

    return -1;
}
