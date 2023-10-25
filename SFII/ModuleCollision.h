#pragma once
#include "Module.h"

struct Collider
{
	SDL_Rect rect;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();


	update_status Update() override;
};

