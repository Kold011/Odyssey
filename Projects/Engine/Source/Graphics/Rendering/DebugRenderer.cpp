#include "DebugRenderer.h"
#include "Shader.h"
#include "ResourceManager.h"
#include "AssetManager.h"
#include "Renderer.h"
#include "VulkanBuffer.h"

namespace Odyssey
{
	void DebugRenderer::Init(Settings settings)
	{
		m_Settings = settings;

		m_Vertices.resize(m_Settings.MaxVertices);
		size_t dataSize = m_Vertices.size() * sizeof(m_Vertices[0]);
		m_VertexBufferID = ResourceManager::Allocate<VulkanBuffer>(BufferType::Vertex, dataSize);
		auto vertexBuffer = ResourceManager::GetResource<VulkanBuffer>(m_VertexBufferID);
		vertexBuffer->UploadData(m_Vertices.data(), dataSize);
	}

	void DebugRenderer::Clear()
	{
		m_VertexCount = 0;
	}

	void DebugRenderer::AddSphere(glm::vec3 center, float radius, glm::vec4 color)
	{
		AddRing(center, { radius, 0, 0, 0 }, { 0, 0, radius, 0 }, color);
		AddRing(center, { radius, 0, 0, 0 }, { 0, radius, 0, 0 }, color);
		AddRing(center, { 0, radius, 0, 0 }, { 0, 0, radius, 0 }, color);
	}

	void DebugRenderer::AddRing(glm::vec3 center, glm::vec4 majorAxis, glm::vec4 minorAxis, glm::vec4 color)
	{
		const size_t ringSegments = 32;
		Vertex vertices[ringSegments + 1];

		constexpr float angleDelta = glm::two_pi<float>() / float(ringSegments);
		float cosDelta = cosf(angleDelta);
		float sinDelta = sinf(angleDelta);

		glm::vec4 incrementalSin = glm::vec4(0, 0, 0, 0);
		const glm::vec4 initialCos = glm::vec4(1, 1, 1, 1);
		glm::vec4 incrementalCos = initialCos;

		for (size_t i = 0; i < ringSegments; i++)
		{
			glm::vec4 pos = (majorAxis * incrementalCos) + glm::vec4(center, 0);
			pos = (minorAxis * incrementalSin) + pos;
			vertices[i].Position = pos;
			vertices[i].Color = color;

			glm::vec4 newCos = (incrementalCos * cosDelta) - (incrementalSin * sinDelta);
			glm::vec4 newSin = (incrementalCos * sinDelta) + (incrementalSin * cosDelta);
			incrementalCos = newCos;
			incrementalSin = newSin;
		}

		vertices[ringSegments] = vertices[0];

		for (size_t i = 0; i < ringSegments; i++)
		{
			m_Vertices[m_VertexCount] = vertices[i];
			++m_VertexCount;
			m_Vertices[m_VertexCount] = vertices[i + 1];
			++m_VertexCount;
		}

	}
	ResourceID DebugRenderer::GetVertexBuffer()
	{
		size_t dataSize = m_Vertices.size() * sizeof(m_Vertices[0]);
		auto vertexBuffer = ResourceManager::GetResource<VulkanBuffer>(m_VertexBufferID);
		vertexBuffer->UploadData(m_Vertices.data(), dataSize);
		return m_VertexBufferID;
	}
}