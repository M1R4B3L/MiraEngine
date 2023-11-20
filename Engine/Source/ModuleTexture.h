#pragma once

#include "Module.h"

#include "DirectXTex.h"


struct Texture
{
	int width;
	int height;
	int format;
	int rowPitch;
	int slicePitch;
	const char* pixels;

};

class ModuleTexture : public Module
{
public:

	ModuleTexture();
	~ModuleTexture() override;

	bool Init() override;
	bool CleanUp() override;

	DirectX::ScratchImage LoadTexture(const char* path);

public: 
	DirectX::ScratchImage baboon;
};

