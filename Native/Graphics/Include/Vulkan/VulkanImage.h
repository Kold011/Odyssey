#pragma once
#include "VulkanGlobals.h"

VK_FWD_DECLARE(VkImage)
VK_FWD_DECLARE(VkDeviceMemory)

namespace Odyssey
{
	enum class ImageType
	{
		None = 0,
		Image2D = 1,
	};

	enum class ImageFormat
	{
		None = 0,
		R8G8B8A8_SRGB = 1
	};

	enum class ImageTiling
	{
		None = 0,
		Optimal = 1,
		Linear = 2,
	};

	struct VulkanImageDescription
	{
		ImageType ImageType = ImageType::None;
		uint32_t Width = 1;
		uint32_t Height = 1;
		uint32_t Depth = 1;
		uint32_t MipLevels = 1;
		uint32_t ArrayLayers = 1;
		uint32_t Samples = 1;
	};

	class VulkanContext;

	class VulkanImage
	{
	public:
		VulkanImage(std::shared_ptr<VulkanContext> context, VulkanImageDescription& desc);

	private:
		uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
	private:
		std::shared_ptr<VulkanContext> m_Context;
		VkImage image;
		VkDeviceMemory imageMemory;
	};
}