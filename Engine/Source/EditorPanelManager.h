#pragma once
class EditorPanelManager
{
public:
	EditorPanelManager();
	EditorPanelManager(const char* name, bool active = true);
	virtual ~EditorPanelManager();

	virtual void Draw();

	const char* GetName();
	bool IsActive();

private:
	const char* panelName = nullptr;
	bool active;
};

