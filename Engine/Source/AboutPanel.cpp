#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleProgram.h"
#include "AboutPanel.h"

#include "imgui.h"

AboutPanel::AboutPanel() : EditorPanelManager("About##", false)
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
		ImGui::Text("Mira by: M1R4B3L (Adrian Mirabel)");
		ImGui::Separator();
		ImGui::TextUnformatted("Mira is a 3D Engine developed for the first Assigment of\nthe 2023 UPC Master Advanced Programing for AAA Videogames");
		ImGui::Spacing();
		ImGui::Text("SDL v2.0");
		ImGui::Text("GLew v2.1.0");
		ImGui::Text("ImGui v1.89.9");
		ImGui::Text("MathGeoLib v1.5");
		ImGui::Text("DirectXTex v2.0.1");
		ImGui::Text("TinyGltf v2.8.10");
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		const char* license = App->program->LoadShaderSource("../../LICENSE");
		ImGui::Text(license);
	}
	ImGui::End();

	return ret;
}
