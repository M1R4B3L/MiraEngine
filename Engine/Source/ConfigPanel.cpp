#include "Application.h"
#include "ModuleWindow.h"
#include "ConfigPanel.h"

#include "imgui.h"

#include "Math/float2.h"


ConfigPanel::ConfigPanel() : EditorPanelManager("Config##", false)
{
	flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
}

ConfigPanel::~ConfigPanel()
{
}

bool ConfigPanel::Draw(int windowFlags)
{
	bool ret = true;

	if (ImGui::Begin(GetName(), &open, windowFlags))
	{
		if (ImGui::CollapsingHeader("Window", flags))
		{
			static int width = App->window->GetWidth();
			static int height = App->window->GetHeight();

			if (ImGui::DragInt("Width", &width, 1, 640, 3840, "%d"))
			{
				App->window->SetWidth(width);
			}
			if (ImGui::DragInt("Height", &height, 1, 480, 2160, "%d"))
			{
				App->window->SetHeight(height);
			}

		}
	}
	ImGui::End();

	return ret;
}
