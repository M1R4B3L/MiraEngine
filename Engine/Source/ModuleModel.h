#pragma once

#include "Module.h"

class ModuleModel : public Module
{public:

	ModuleModel();
	~ModuleModel() override;

	bool Init() override;
	bool CleanUp() override;
};

class Mesh
{


};