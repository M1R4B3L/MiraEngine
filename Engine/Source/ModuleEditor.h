#pragma once
#include "Module.h"

class Application;
struct ImGuiIO;

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor() override;

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	void Draw(ImGuiIO& io);

private:
	ImGuiIO* io = nullptr;
};

