#pragma once

#include "EditorPanelManager.h"

class MenuBarPanel : public EditorPanelManager
{
public:
	MenuBarPanel();
	~MenuBarPanel();

	bool Draw(int windowFlags) override;

};

