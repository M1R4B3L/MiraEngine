#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ConfigPanel.h"

#include "imgui.h"

#include "MathGeoLib.h"


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
			int width = App->window->GetWidth();
			int height = App->window->GetHeight();

			if (ImGui::DragInt("Width", &width, 1, 640, 3840, "%d"))
			{
				App->window->SetWidth(width);
			}
			if (ImGui::DragInt("Height", &height, 1, 480, 2160, "%d"))
			{
				App->window->SetHeight(height);
			}

		}
		if (ImGui::CollapsingHeader("Camera", flags))
		{
			Frustum frustum = App->camera->frustum;
			float3 cameraPos = frustum.pos;
			ImGui::Text("Pos");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##Pos",(float*) &cameraPos, 1))
			{
				App->camera->frustum.pos = cameraPos;
			}

			//TODO DO IT PROPERLY 
			float3 angles = float3::zero;
			if (ImGui::DragFloat3("Rot", (float*)&angles, 1))
			{
				App->camera->RotateAxisAngle(float3::unitX, angles.x);
				App->camera->RotateAxisAngle(float3::unitY, angles.y);
				App->camera->RotateAxisAngle(float3::unitZ, angles.z);
			}
			
			float nearPlane = frustum.nearPlaneDistance;
			float farPlane = frustum.farPlaneDistance;
			ImGui::Text("Camera Planes");
			ImGui::PushItemWidth(100);
			if (ImGui::DragFloat("Near", (float*)&nearPlane, 1.0f, 1.0f, NULL, "%.1f"))
			{
				App->camera->SetNearPlanePos(nearPlane);
			}
			ImGui::PushItemWidth(100);
			if (ImGui::DragFloat("Far", (float*)&farPlane, 1.0f, 1.0f, NULL, "%.1f"));
			{
				App->camera->SetFarPlanePos(farPlane);
			}

			ImGui::Separator();
			ImGui::Dummy(ImVec2(0.0f, 20.0f));
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Separator();

			float vFov = math::RadToDeg(frustum.verticalFov);
			float hFov = math::RadToDeg(frustum.horizontalFov);
			ImGui::Text("Field of View (FOV)");
			ImGui::Text("Horitzontal");
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			if (ImGui::DragFloat("##H", &hFov,1.0f))
			{
				App->camera->SetFOV(hFov);
			}
			ImGui::PushItemWidth(100);
			ImGui::DragFloat("Vertical", &vFov,1.0f, 0.0f, 0.0f, "%.3f", ImGuiSliderFlags_NoInput);


		}
	}
	ImGui::End();

	return ret;
}