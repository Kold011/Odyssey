#pragma once
#include "Resource.h"
#include "VulkanGlobals.h"
#include "VulkanImage.h"
#include "VulkanTextureSampler.h"

namespace Odyssey
{
	class VulkanContext;
	class VulkanBuffer;
	class VulkanRenderTexture : public Resource
	{
	public:
		VulkanRenderTexture(ResourceID id, std::shared_ptr<VulkanContext> context, uint32_t width, uint32_t height);
		VulkanRenderTexture(ResourceID id, std::shared_ptr<VulkanContext> context, uint32_t width, uint32_t height, TextureFormat format);
		VulkanRenderTexture(ResourceID id, std::shared_ptr<VulkanContext> context, VulkanImageDescription& imageDesc);
		VulkanRenderTexture(ResourceID id, std::shared_ptr<VulkanContext> context, ResourceID imageID, TextureFormat format);
		void Destroy();

	public:
		void SetData(BinaryBuffer& buffer);

	public:
		ResourceID GetImage() { return m_Image; }
		ResourceID GetResolveImage() { return m_ResolveImage; }
		ResourceID GetSampler() { return m_Sampler; }
		uint32_t GetWidth() { return m_Width; }
		uint32_t GetHeight() { return m_Height; }
		TextureFormat GetFormat() { return m_Format; }

	public:
		VkWriteDescriptorSet GetDescriptorInfo();

	private:
		bool IsDepthTexture(TextureFormat format);

	private:
		std::shared_ptr<VulkanContext> m_Context;
		ResourceID m_Image;
		ResourceID m_ResolveImage;
		ResourceID m_StagingBuffer;
		ResourceID m_Sampler;
		uint32_t m_Width, m_Height;
		TextureFormat m_Format;
		VkDescriptorImageInfo descriptor;
	};
}