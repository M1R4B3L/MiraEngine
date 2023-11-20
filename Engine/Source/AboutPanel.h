#pragma once

#include "EditorPanelManager.h"


class AboutPanel : public EditorPanelManager
{
public: 
	AboutPanel();
	~AboutPanel();

	bool Draw(int windowFlags) override;

};

