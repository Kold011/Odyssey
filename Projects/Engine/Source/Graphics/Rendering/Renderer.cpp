#include "Renderer.h"
#include "VulkanRenderer.h"

namespace Odyssey
{
	void Renderer::Init(const RendererConfig& config)
	{
		s_Config = config;
		s_RendererAPI = std::make_shared<VulkanRenderer>();

		if (s_Config.EnableIMGUI)
			s_RendererAPI->AddImguiPass();
	}

	bool Renderer::Update()
	{
		return s_RendererAPI->Update();
	}

	bool Renderer::Render()
	{
		return s_RendererAPI->Render();
	}

	void Renderer::Destroy()
	{
		s_RendererAPI->Destroy();
	}

	void Renderer::PushRenderPass(std::shared_ptr<RenderPass> renderPass)
	{
		s_RendererAPI->AddRenderPass(renderPass);
	}

	void Renderer::SetDrawGUIListener(std::function<void(void)> listener)
	{
		s_RendererAPI->GetImGui()->SetDrawGUIListener(listener);
	}
	int64_t Renderer::AddImguiTexture(ResourceHandle<VulkanRenderTexture> textureHandle, ResourceHandle<VulkanTextureSampler> samplerHandle)
	{
		return s_RendererAPI->GetImGui()->AddTexture(textureHandle, samplerHandle);
	}
	std::shared_ptr<VulkanWindow> Renderer::GetWindow()
	{
		return s_RendererAPI->GetWindow();
	}
}