#pragma once
#include "VulkanGlobals.h"
#include "Enums.h"

VK_FWD_DECLARE(VkDescriptorSetLayout)

namespace Odyssey
{
	class VulkanContext;

	class VulkanDescriptorLayout
	{
	public:
		VulkanDescriptorLayout(std::shared_ptr<VulkanContext> context, DescriptorType type, ShaderStage shaderStag, uint32_t bindingIndex);

	private:
		std::shared_ptr<VulkanContext> m_Context;
		DescriptorType m_Type;
		ShaderStage m_ShaderStage;
		uint32_t m_BindingIndex;
		VkDescriptorSetLayout m_Layout = VK_NULL_HANDLE;
	};
}