#include "VulkanVertex.h"

namespace Odyssey
{
	VulkanVertex::VulkanVertex(glm::vec3 position, glm::vec3 color)
	{
		m_Position = position;
		m_Color = color;
	}

	VulkanVertex::VulkanVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 uv0)
	{
		m_Position = position;
		m_Normal = normal;
		m_UV0 = uv0;
	}

	VkVertexInputBindingDescription VulkanVertex::GetBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription;
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(VulkanVertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	std::array<VkVertexInputAttributeDescription, 4> VulkanVertex::GetAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions;

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(VulkanVertex, m_Position);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(VulkanVertex, m_Color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(VulkanVertex, m_Normal);

		attributeDescriptions[3].binding = 0;
		attributeDescriptions[3].location = 3;
		attributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[3].offset = offsetof(VulkanVertex, m_UV0);

		return attributeDescriptions;
	}
}