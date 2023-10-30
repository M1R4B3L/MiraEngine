#pragma once
#include "Module.h"
#include "imgui.h"

class Application;

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor() override;

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	ImGuiIO io;
};

