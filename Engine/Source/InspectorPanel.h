#pragma once
#include "EditorPanelManager.h"

class InspectorPanel : public EditorPanelManager
{
public:

	InspectorPanel();
	~InspectorPanel();

	bool Draw(int windowFlags) override;
};

