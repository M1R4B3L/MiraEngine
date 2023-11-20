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

			ImGui::DragInt("Width", &width, 1, 640, 3840, "%d", ImGuiSliderFlags_AlwaysClamp);
			ImGui::DragInt("Height", &height, 1, 480, 2160, "%d", ImGuiSliderFlags_AlwaysClamp);

			App->window->SetWidth(width);
			App->window->SetHeight(height);
		}
	}
	ImGui::End();

	return ret;
}
