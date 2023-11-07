#include "EditorPanelManager.h"

EditorPanelManager::EditorPanelManager()
{
}

EditorPanelManager::EditorPanelManager(const char* name, bool active)
{
    panelName = name;
    isActive = active;
    isHovered = false;
    isClicked = false;
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
    return panelName;
}

bool EditorPanelManager::IsActive()
{
    return isActive;
}
