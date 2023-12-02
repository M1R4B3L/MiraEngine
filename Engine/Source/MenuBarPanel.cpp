#include "Application.h"
#include "ModuleEditor.h"

//TODO: ADD AND ID TO PANELS AND A FUNCTION TO SEARCH FOR ID INSTEAD OF INCLUDE
#include "MenuBarPanel.h"
#include "AboutPanel.h"
#include "ConfigPanel.h"

#include "imgui.h"
#include "imgui_internal.h"

#include <string>

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

		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Config")) 
			{
				if (!App->editor->config->IsOpen())
					App->editor->config->Open();
				else
					App->editor->config->Close();
			}

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
			if (ImGui::BeginMenu("3D"))
			{
				if (ImGui::MenuItem("fish_hat.c"))
				{
					
				}

				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::BeginMenu("Open Panels"))
			{
				//TODO: CREATE VECTOR FOR OPEN PANELS AND HANDLE THEM
				std::vector<EditorPanelManager*> panels = App->editor->editorPanels;
				unsigned i = 0;
				for (std::vector<EditorPanelManager*>::iterator it = panels.begin(); (it != panels.end()); ++it, ++i)
				{
					std::string name = std::to_string(i) + ' ' + (*it)->GetName();
					if ((*it)->IsOpen() && name.compare("0 Menu Bar##") != 0)
					{
						if (ImGui::MenuItem(name.c_str(), "", (*it)->IsOpen()))
						{
							//Set To selected Panel and Open if docked
						}
					}
				}		
				ImGui::EndMenu();
			}
			//OPEN CLOSED PANELS
			//TODO ADD TAG TO PANELS OR CREATE OTHER VECTOR FOR EACH TAG
			ImGui::Separator();
			if (ImGui::BeginMenu("General"))
			{
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

		if (ImGui::BeginMenu("Quit"))
		{
			ret = false;

			ImGui::EndMenu();
		}
	}
	ImGui::EndMainMenuBar();

	return ret;
}