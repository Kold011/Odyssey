#include "CameraInspector.h"
#include <Camera.h>
#include <ComponentManager.h>
#include <imgui.h>

namespace Odyssey
{
	CameraInspector::CameraInspector(GameObject go)
	{
		m_GameObject = go;

		if (Camera* camera = ComponentManager::GetComponent<Camera>(m_GameObject))
		{
			std::function<void(float)> fovModified = [go](float fov)
				{
					if (Camera* camera = ComponentManager::GetComponent<Camera>(go))
					{
						camera->SetFieldOfView(fov);
					}
				};

			std::function<void(float)> nearClipModified = [go](float nearClip)
				{
					if (Camera* camera = ComponentManager::GetComponent<Camera>(go))
					{
						camera->SetNearClip(nearClip);
					}
				};

			std::function<void(float)> farClipModified = [go](float farClip)
				{
					if (Camera* camera = ComponentManager::GetComponent<Camera>(go))
					{
						camera->SetFarClip(farClip);
					}
				};

			m_FieldOfViewDrawer = FloatDrawer("Field of View", camera->GetFieldOfView(), fovModified);
			m_NearClipDrawer = FloatDrawer("Near Clip", camera->GetNearClip(), nearClipModified);
			m_FarClipDrawer = FloatDrawer("Far Clip", camera->GetFarClip(), farClipModified);
		}
	}
	void CameraInspector::Draw()
	{
		if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
		{
			if (ImGui::BeginTable("CameraInspector", 2, ImGuiTableFlags_::ImGuiTableFlags_SizingMask_))
			{
				ImGui::TableSetupColumn("##A", 0, 0.4f);
				m_FieldOfViewDrawer.Draw();
				ImGui::TableNextRow();
				m_NearClipDrawer.Draw();
				ImGui::TableNextRow();
				m_FarClipDrawer.Draw();
				ImGui::EndTable();
			}
		}

		ImGui::Separator();
	}
}