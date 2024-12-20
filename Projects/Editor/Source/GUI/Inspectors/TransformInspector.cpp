#include "TransformInspector.h"
#include "GameObject.h"
#include "Transform.h"
#include "imgui.h"
#include "Preferences.h"

namespace Odyssey
{
	TransformInspector::TransformInspector(GameObject& gameObject)
	{
		m_GameObject = gameObject;

		if (Transform* transform = m_GameObject.TryGetComponent<Transform>())
		{
			positionDrawer = Vector3Drawer("Position", transform->m_Position, glm::vec3(0, 0, 0), true,
				[this](glm::vec3 position) { OnPositionChanged(position); });

			rotationDrawer = Vector3Drawer("Rotation", transform->m_EulerRotation, glm::vec3(0, 0, 0), true,
				[this](glm::vec3 rotation) { OnRotationChanged(rotation); });

			scaleDrawer = Vector3Drawer("Scale", transform->m_Scale, glm::vec3(1, 1, 1), true,
				[this](glm::vec3 scale) { OnScaleChanged(scale); });
		}
	}

	bool TransformInspector::Draw()
	{
		bool modified = false;

		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
		{
			Transform& transform = m_GameObject.GetComponent<Transform>();
			positionDrawer.SetValue(transform.GetPosition());
			rotationDrawer.SetValue(transform.GetEulerRotation());
			scaleDrawer.SetValue(transform.GetScale());

			modified |= positionDrawer.Draw();
			modified |= rotationDrawer.Draw();
			modified |= scaleDrawer.Draw();

			struct Data
			{
				float3 pos, rot, scale;
			};

			if (ImGui::Button("Copy"))
			{
				Data data{ positionDrawer.GetValue(), rotationDrawer.GetValue(), scaleDrawer.GetValue() };
				ClipBoard::Copy("Transform", &data, sizeof(data));
			}

			ImGui::SameLine();

			if (ImGui::Button("Paste"))
			{
				if (ClipBoard::GetContext() == "Transform")
				{
					Data data = ClipBoard::Paste().Read<Data>();

					OnPositionChanged(data.pos);
					OnRotationChanged(data.rot);
					OnScaleChanged(data.scale);
				}
			}
		}

		ImGui::Spacing();

		return modified;
	}

	void TransformInspector::OnPositionChanged(glm::vec3 position)
	{
		if (Transform* transform = m_GameObject.TryGetComponent<Transform>())
			transform->SetPosition(position);
	}

	void TransformInspector::OnRotationChanged(glm::vec3 rotation)
	{
		if (Transform* transform = m_GameObject.TryGetComponent<Transform>())
		{
			transform->SetRotation(rotation);
		}
	}

	void TransformInspector::OnScaleChanged(glm::vec3 scale)
	{
		if (Transform* transform = m_GameObject.TryGetComponent<Transform>())
			transform->SetScale(scale);
	}
}