#include "VulkanUniformBuffer.h"
#include "VulkanContext.h"

namespace Odyssey
{
	VulkanUniformBuffer::VulkanUniformBuffer(std::shared_ptr<VulkanContext> context, BufferType bufferType, uint32_t bindingIndex, VkDeviceSize size)
		: VulkanBuffer(context, bufferType, size)
	{
		m_BindingIndex = bindingIndex;

		descriptor.buffer = buffer;
		descriptor.range = VK_WHOLE_SIZE;
		descriptor.offset = 0;
	}

	VkWriteDescriptorSet VulkanUniformBuffer::GetDescriptorInfo()
	{
		VkWriteDescriptorSet writeSet{};
		writeSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeSet.dstSet = 0;
		writeSet.dstBinding = m_BindingIndex;
		writeSet.descriptorCount = 1;
		writeSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		writeSet.pBufferInfo = &descriptor;
		return writeSet;
	}
}