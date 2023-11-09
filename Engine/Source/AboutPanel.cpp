#include "Application.h"
#include "ModuleEditor.h"
#include "AboutPanel.h"

#include "imgui.h"

AboutPanel::AboutPanel() : EditorPanelManager("About", false)
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
		if (!open)
			CloseWindow();


	}
	ImGui::End();

	return ret;
}
