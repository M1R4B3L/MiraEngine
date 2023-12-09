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
class InspectorPanel;

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:

	void embraceTheDarkness() const;
	void drakula() const;

	bool CreateDockWindow(const char* name, bool open, int windowFlags);

public:
	bool demo;

	std::vector<EditorPanelManager*> editorPanels;

	AboutPanel* about = nullptr;
	MenuBarPanel* menuBar = nullptr;
	ConfigPanel* config = nullptr;
	ConsolePanel* console = nullptr;
	InspectorPanel* inspector = nullptr;

private:
	ImGuiIO* io = nullptr;
	
};

