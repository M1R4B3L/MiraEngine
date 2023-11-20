#include "Application.h"
#include "ModuleEditor.h"
#include "MenuBarPanel.h"
#include "AboutPanel.h"

#include "imgui.h"
#include "imgui_internal.h"

MenuBarPanel::MenuBarPanel() : EditorPanelManager("Menu Bar##", true)
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
		if (ImGui::BeginMenu("File")) 
		{
			if (ImGui::MenuItem("New Scene")) {}
			if (ImGui::MenuItem("Open Scene")) {}
			if (ImGui::MenuItem("Save Scene")) {}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("GameObject"))
		{
			if (ImGui::BeginMenu("2D"))
			{
				if(ImGui::MenuItem("fish_hat.c"))
				{

				}

				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help")) 
		{
			//Vaya puto tilt
			ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
			if (ImGui::MenuItem(App->editor->about->GetName(), NULL, App->editor->about->IsOpen()))
			{
				if (!App->editor->about->IsOpen())
					App->editor->about->Open();
				else
					App->editor->about->Close();
			}
			if (ImGui::MenuItem("ImGui Demo", NULL, App->editor->demo))
			{
				if (!App->editor->demo)
					App->editor->demo = true;
				else
					App->editor->demo = false;
			}
			ImGui::PopItemFlag();
			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();

	return ret;
}