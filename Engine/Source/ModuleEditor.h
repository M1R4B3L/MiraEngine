#pragma once

#include <vector>

#include "Module.h"

struct ImGuiIO;

class Application;
class EditorPanelManager;

class AboutPanel;
class MenuBarPanel;
class ConfigPanel;
class ConsolePanel;

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

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
	ConsolePanel* console;

private:
	ImGuiIO* io = nullptr;
	
};

