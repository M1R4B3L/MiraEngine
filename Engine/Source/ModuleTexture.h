#pragma once
#include "Module.h"

#include "DirectXTex.h"

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

