#include "Application.h"
#include "ModuleEditor.h"
#include "AboutPanel.h"

#include "imgui.h"

AboutPanel::AboutPanel() : EditorPanelManager("About", true)
{
}

AboutPanel::~AboutPanel()
{
}

bool AboutPanel::Draw(int windowFlags)
{
	bool ret = true;

	if (ImGui::Begin(GetName(), &open, windowFlags))
	{
		
	}
	ImGui::End();

	return ret;
}
