#include "Globals.h"
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

	static bool open = true;

	if (open)
	{
		if (ImGui::Begin(GetName(), &open, windowFlags))
		{
			
		}

		ImGui::End();
	}

	return ret;
}
