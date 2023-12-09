#include "Application.h"
#include "ModuleModel.h"
#include "ModuleTexture.h"

#include "EditorPanelManager.h"
#include "InspectorPanel.h"

#include "imgui.h"

InspectorPanel::InspectorPanel() : EditorPanelManager("Inspector##", true)
{

}

InspectorPanel::~InspectorPanel()
{
}

bool InspectorPanel::Draw(int windowFlags)
{
	bool ret = true;

	if (ImGui::Begin(GetName(), &open, windowFlags))
	{
		for (int i = 0; i < App->model->meshes.size(); ++i)
		{
			Mesh* mesh = App->model->meshes[i];
		
			ImGui::Text(mesh->name.c_str());
			ImGui::SameLine();
			ImGui::Text(":");
			ImGui::Spacing();
			ImGui::Text("Vertices Count: %u", mesh->numVert);
			ImGui::Text("Indices Count: %u", mesh->numInd);
			unsigned triCount = mesh->numVert / 3;
			if (mesh->numInd != 0)
				triCount = mesh->numInd / 3;
			ImGui::Text("Triangles Count: %u", triCount);
			if(App->model->textures.size() > 0)
				ImGui::Image((void*)(intptr_t)App->model->textures[mesh->disffuseMat]->id, ImVec2(100, 100));
			ImGui::Separator();
			
		}
		ImGui::End();
	}
	return ret;
}
