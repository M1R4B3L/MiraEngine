#pragma once

class EditorPanelManager
{
public:
	EditorPanelManager();
	EditorPanelManager(const char* name, bool open = true);
	virtual ~EditorPanelManager();

	virtual bool Draw(int windowFlags = 0);

	const char* GetName();
	bool IsOpen();
	bool IsHovered();
	bool isCliked();

protected:
	bool open;

private:
	const char* name = nullptr;

	bool hovered;
	bool clicked;
};

