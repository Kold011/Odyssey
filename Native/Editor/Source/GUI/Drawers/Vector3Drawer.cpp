#include "Vector3Drawer.h"
#include <imgui.h>

namespace Odyssey::Editor
{
	Vector3Drawer::Vector3Drawer(const std::string& propertyLabel, Vector3 vec3, std::function<void(Vector3)> callback)
	{
		label = propertyLabel;
		data = { vec3.x, vec3.y, vec3.z };
		onValueModified = callback;
	}

	void Vector3Drawer::Draw()
	{
		ImGui::TableNextColumn();
		ImGui::TextUnformatted(label.data());
		ImGui::TableNextColumn();
		ImGui::PushItemWidth(-0.01f);
		if (ImGui::InputFloat3(label.data(), data.data()))
		{
			onValueModified(Vector3(data[0], data[1], data[2]));
		}
	}
}