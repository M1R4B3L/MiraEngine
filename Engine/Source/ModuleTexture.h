#pragma once

#include "Module.h"

#include "DirectXTex.h"


struct Texture
{
	unsigned id;
	int width;
	int height;
	int format;

	const char* name;

	uint8_t* pixels;
};

class ModuleTexture : public Module
{
public:

	ModuleTexture();
	~ModuleTexture();

	bool Init() override;
	bool CleanUp() override;

	unsigned LoadTexture(const char* path);

public: 

};

