#pragma once
#include "Inspector.h"
#include "Vector3Drawer.h"
#include "PropertyDrawer.h"
#include "GameObject.h"

namespace Odyssey
{
	class GameObject;

	class TransformInspector : public Inspector
	{
	public:
		TransformInspector() = default;
		TransformInspector(GameObject& gameObject);

	public:
		virtual void Draw() override;

	private:
		void OnPositionChanged(glm::vec3 position);
		void OnRotationChanged(glm::vec3 rotation);
		void OnScaleChanged(glm::vec3 scale);

	private:
		GameObject m_GameObject;
		Vector3Drawer positionDrawer;
		Vector3Drawer rotationDrawer;
		Vector3Drawer scaleDrawer;
	};
}