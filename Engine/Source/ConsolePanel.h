#pragma once
#include "EditorPanelManager.h"

class ConsolePanel : public EditorPanelManager
{
public:

	ConsolePanel();
	~ConsolePanel();

	bool Draw(int windowFlags) override;

	void AddLog(const char* text);
	void ClearLog();

	std::vector<const char*> logs;
};

