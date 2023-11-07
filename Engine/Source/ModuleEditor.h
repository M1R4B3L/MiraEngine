#pragma once
#include <vector>

#include "Module.h"

class Application;
class EditorPanelManager;

struct ImGuiIO;

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor() override;

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:

	bool CreateRootDockWindow(const char* name, bool open, int windowFlags);

public:
	std::vector<EditorPanelManager*> editorPanels;

private:
	ImGuiIO* io = nullptr;
	
};

