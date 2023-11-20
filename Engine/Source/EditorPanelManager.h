#pragma once

class EditorPanelManager
{
public:
	EditorPanelManager();
	EditorPanelManager(const char* name, bool open = true);
	virtual ~EditorPanelManager();

	virtual bool Draw(int windowFlags = 0);

	const char* GetName()const;
	bool IsOpen()const;
	bool IsHovered()const;
	bool IsSelected()const;

	bool Open();
	bool Close();


	void SetIsHovered();
	void SetIsSelected();

protected:
	bool open;

private:
	const char* name = nullptr;
	bool hovered;
	bool selected;
};

