#pragma once
#include <GUIElement.h>
#include "glm.h"
#include "ResourceHandle.h"

namespace Odyssey
{
	class VulkanTexture;
	class OpaquePass;

	class SceneViewWindow : public GUIElement
	{
	public:
		SceneViewWindow();
		virtual void Update() override;
		virtual void Draw() override;
		void Destroy();

	public:
		std::shared_ptr<OpaquePass> GetRenderPass() { return m_SceneViewPass; }

		void SetSelectedIndex(uint32_t selected) { m_SelectedObject = selected; }

	private:
		void RenderGizmos();
		void UpdateCameraController();
		void UpdateGizmosInput();

	private:
		bool m_CameraControllerInUse = false;

	private: // Rendering stuff
		std::shared_ptr<OpaquePass> m_SceneViewPass;
		uint64_t m_RenderTextureID;
		ResourceHandle<VulkanTexture> m_RenderTexture;

	private: // Window stuff
		bool open = true;
		uint32_t m_SelectedObject;
		glm::vec2 m_WindowPos;
		glm::vec2 m_WindowSize;
		glm::vec2 m_WindowMin;
		glm::vec2 m_WindowMax;
		uint32_t op = 7;
	};
}