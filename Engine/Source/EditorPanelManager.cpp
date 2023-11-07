#include "EditorPanelManager.h"

EditorPanelManager::EditorPanelManager()
{
}

EditorPanelManager::EditorPanelManager(const char* name_, bool active_)
{
    name = name_;
    open = active_;
    hovered = false;
    clicked = false;
}

EditorPanelManager::~EditorPanelManager()
{
}

bool EditorPanelManager::Draw(int windowFlags)
{
    return true;
}

const char* EditorPanelManager::GetName()
{
    return name;
}

bool EditorPanelManager::IsOpen()
{
    return open;
}
