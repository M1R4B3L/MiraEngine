#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleCamera.h"
#include "ModuleOpenGL.h"
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
		if (ImGui::CollapsingHeader("OpenGl", flags))
		{
			ImGui::Text("CPUs: ");
			ImGui::Text("GPU: ");
			ImGui::Text("Brand: ");
		}
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

		if (ImGui::CollapsingHeader("Input", flags))
		{	
			ImGui::Text("Mouse Pos: ");
			ImGui::SameLine();
			ImGui::Text("(%.0f,%.0f)", App->input->GetMousePos().x, App->input->GetMousePos().y);

			ImGui::Text("Mouse Motion: ");
			ImGui::SameLine();
			ImGui::Text("(%.0f,%.0f)", App->input->GetMouseMotion().x, App->input->GetMouseMotion().y);
		}
		if (ImGui::CollapsingHeader("Camera", flags))
		{
			float camSpeed = App->camera->GetCameraSpeed();
			ImGui::Text("Camera Speed");
			if (ImGui::DragFloat("##Speed", (float*)&camSpeed, 0.01))
			{
				App->camera->SetCameraSpeed(camSpeed);
			}
			ImGui::Separator();

			Frustum frustum = App->camera->GetFrustum();
			float3 cameraPos = frustum.pos;
			ImGui::Text("Pos");
			ImGui::SameLine();
			if (ImGui::DragFloat3("##Pos",(float*) &cameraPos, 1))
			{
				App->camera->SetFrustumPos(cameraPos);
			}
			//TODO DO IT PROPERLY 
			float3 angles = float3::zero;
			if (ImGui::DragFloat3("Rot", (float*)&angles, 1))
			{
				App->camera->Rotate(float3::unitX, angles.x);
				App->camera->Rotate(float3::unitY, angles.y);
				App->camera->Rotate(float3::unitZ, angles.z);
			}
			
			float nearPlane = frustum.nearPlaneDistance;
			float farPlane = frustum.farPlaneDistance;
			ImGui::Text("Camera Planes");
			ImGui::PushItemWidth(100);
			if (ImGui::DragFloat("Near", (float*)&nearPlane, 1.0f, 1.0f, NULL, "%.2f"))
			{
				App->camera->SetNearPlanePos(nearPlane);
			}
			ImGui::PushItemWidth(100);
			if (ImGui::DragFloat("Far", (float*)&farPlane, 1.0f, 1.0f, NULL, "%.2f"))
			{
				App->camera->SetFarPlanePos(farPlane);
			}

			ImGui::Separator();

			float vFov = math::RadToDeg(frustum.verticalFov);
			float hFov = math::RadToDeg(frustum.horizontalFov);
			ImGui::Text("Field of View (FOV)");
			ImGui::Text("Horitzontal");
			ImGui::SameLine();
			ImGui::PushItemWidth(100);
			if (ImGui::DragFloat("##H", &hFov, 1.0f))
			{
				App->camera->SetFOV(hFov);
			}
			ImGui::PushItemWidth(100);
			ImGui::DragFloat("Vertical", &vFov, 1.0f, 0.0f, 0.0f, "%.3f", ImGuiSliderFlags_NoInput);

			ImGui::Dummy(ImVec2(0.0f, 20.0f));
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Separator();
		}
	}
	ImGui::End();

	return ret;
}
