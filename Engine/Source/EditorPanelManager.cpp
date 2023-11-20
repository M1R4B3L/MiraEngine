#include "EditorPanelManager.h"

EditorPanelManager::EditorPanelManager()
{
}

EditorPanelManager::EditorPanelManager(const char* name_, bool active_)
{
    name = name_;
    open = active_;
    hovered = false;
    selected = false;
}

EditorPanelManager::~EditorPanelManager()
{
}

bool EditorPanelManager::Draw(int windowFlags)
{
    bool ret = true;

    return ret;
}

const char* EditorPanelManager::GetName() const
{
    return name;
}

bool EditorPanelManager::IsOpen() const
{
    return open;
}

bool EditorPanelManager::IsHovered() const
{
    return hovered;
}

bool EditorPanelManager::IsSelected() const
{
    return selected;
}

bool EditorPanelManager::Open()
{
    if (open == false)
    {
        open = true;
    }

	return open;
}

bool EditorPanelManager::Close()
{
    if (open == true)
    {
        open = false;
    }

    return open;
}
