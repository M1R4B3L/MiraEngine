#include "Application.h"
#include "ModuleEditor.h"

#include "EditorPanelManager.h"
#include "ConsolePanel.h"

#include "imgui.h"

ConsolePanel::ConsolePanel() : EditorPanelManager("Console##", true)
{
	autoScroll = true;
}

ConsolePanel::~ConsolePanel()
{
	ClearLog();
}

bool ConsolePanel::Draw(int windowFlags)
{
	bool ret = true;

	if (ImGui::Begin(GetName(), &open, windowFlags))
	{
		for (int i = 0; i < logs.size(); ++i)
		{
			//TODO add color, error tags, filters, search, input,etc.
			ImGui::TextUnformatted(logs[i]);
		}

		if(autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::End();
	}

	return ret;
}

void ConsolePanel::AddLog(const char* text)
{
	size_t len = std::strlen(text) + 1;
	void* buff = malloc(len);
	if(buff != nullptr)
		memcpy(buff, (const void*)text, len);

	logs.push_back((char*)buff);
}

void ConsolePanel::ClearLog()
{
	for (int i = 0; i < logs.size(); ++i)
		free((void*)logs[i]);
}
