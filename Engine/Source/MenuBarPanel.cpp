#include "Application.h"
#include "ModuleEditor.h"
#include "MenuBarPanel.h"
#include "AboutPanel.h"
#include "imgui.h"

MenuBarPanel::MenuBarPanel() : EditorPanelManager("Menu Bar", true)
{
}

MenuBarPanel::~MenuBarPanel()
{
}

bool MenuBarPanel::Draw(int windowFlags)
{
	bool ret = true;
	
	if (ImGui::BeginMainMenuBar())
	{
        if (ImGui::BeginMenu("File")) {

            if (ImGui::MenuItem("Create")) {
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Windows")) {

            if (ImGui::MenuItem("About", NULL, App->editor->about->IsOpen())) {
                
                if (App->editor->about->IsOpen())
                    App->editor->about->CloseWindow();
                else
                    App->editor->about->OpenWindow();
            }
            ImGui::EndMenu();
        }
	}
	ImGui::EndMainMenuBar();

	return ret;
}
