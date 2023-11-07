#include "EditorPanelManager.h"

EditorPanelManager::EditorPanelManager()
{
}

EditorPanelManager::EditorPanelManager(const char* name, bool isActive)
{
}

EditorPanelManager::~EditorPanelManager()
{
}

void EditorPanelManager::Draw()
{

}

const char* EditorPanelManager::GetName()
{
    return panelName;
}

bool EditorPanelManager::IsActive()
{
    return active;
}
