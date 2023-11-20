#pragma once

#include "EditorPanelManager.h"


class ConfigPanel : public EditorPanelManager
{
public:
	ConfigPanel();
	~ConfigPanel();

	bool Draw(int windowFlags) override;

	unsigned flags;
};

