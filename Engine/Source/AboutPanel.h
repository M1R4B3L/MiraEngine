#pragma once
#include "EditorPanelManager.h"

class AboutPanel : public EditorPanelManager
{
public:
	AboutPanel();
	~AboutPanel();

	void Draw() override;
};

