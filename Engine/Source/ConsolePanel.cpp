#include "Application.h"
#include "ModuleEditor.h"

#include "EditorPanelManager.h"
#include "ConsolePanel.h"

#include "imgui.h"

ConsolePanel::ConsolePanel() : EditorPanelManager("Console##", true)
{
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
			ImGui::Text("%d",i);
			ImGui::SameLine();
			ImGui::TextUnformatted(logs[i]);
		}

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
