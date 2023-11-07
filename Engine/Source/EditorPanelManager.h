#pragma once

class EditorPanelManager
{
public:
	EditorPanelManager();
	EditorPanelManager(const char* name, bool active = true);
	virtual ~EditorPanelManager();

	virtual bool Draw(int windowFlags = 0);

	const char* GetName();
	bool IsActive();

private:
	const char* panelName = nullptr;
	bool isActive;
	bool isHovered;
	bool isClicked;
};

