#include "TransformInspector.h"
#include <Transform.h>
#include <ComponentManager.h>
#include <imgui.h>

namespace Odyssey::Editor
{
	TransformInspector::TransformInspector(Entities::GameObject go)
	{
		using namespace Entities;

		gameObject = go;

		if (Transform* transform = ComponentManager::GetComponent<Transform>(go))
		{
			// Callback for when the position is modified through the drawer
			std::function<void(Vector3)> positionModified = [go](Vector3 position)
				{
					if (Transform* transform = ComponentManager::GetComponent<Transform>(go))
					{
						transform->position = position;
					}
				};

			// Callback for when the rotation is modified through the drawer
			std::function<void(Vector3)> rotationModified = [this](Vector3 rotation)
				{
					if (Transform* transform = ComponentManager::GetComponent<Transform>(gameObject))
					{
						transform->eulerRotation = rotation;
					}
				};

			// Callback for when the scale is modified through the drawer
			std::function<void(Vector3)> scaleModified = [this](Vector3 scale)
				{
					if (Transform* transform = ComponentManager::GetComponent<Transform>(gameObject))
					{
						transform->scale = scale;
					}
				};

			positionDrawer = Vector3Drawer("Position", transform->position, positionModified);
			rotationDrawer = Vector3Drawer("Rotation", transform->eulerRotation, rotationModified);
			scaleDrawer = Vector3Drawer("Scale", transform->scale, scaleModified);
		}
	}

	void TransformInspector::Draw()
	{
		if (ImGui::CollapsingHeader("Transform"))
		{
			if (ImGui::BeginTable("TransformInspector", 2, ImGuiTableFlags_::ImGuiTableFlags_SizingMask_))
			{
				ImGui::TableSetupColumn("##A", 0, 0.4f);
				positionDrawer.Draw();
				ImGui::TableNextRow();
				rotationDrawer.Draw();
				ImGui::TableNextRow();
				scaleDrawer.Draw();
				ImGui::EndTable();
			}
		}

		ImGui::Separator();
	}
}