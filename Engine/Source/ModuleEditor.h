#pragma once

#include <vector>

#include "Module.h"

struct ImGuiIO;

class Application;
class EditorPanelManager;

class AboutPanel;
class MenuBarPanel;
class ConfigPanel;

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor() override;

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:

	void embraceTheDarkness();
	void drakula();

	bool CreateDockWindow(const char* name, bool open, int windowFlags);

public:
	bool demo;

	std::vector<EditorPanelManager*> editorPanels;

	AboutPanel* about;
	MenuBarPanel* menuBar;
	ConfigPanel* config;

private:
	ImGuiIO* io = nullptr;
	
};

