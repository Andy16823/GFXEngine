#include "PositionMesh.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;
using namespace GFXEngine::EngineTypes;

void GFXEngine::Graphics::PositionMesh::init(Renderer& renderer)
{
	auto vertexBufferSize = m_vertices.size() * sizeof(PositionVertex);

	auto vertexStagingBuffer = renderer.createBuffer(
		vertexBufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(vertexStagingBuffer, m_vertices.data(), vertexBufferSize);
	
	m_vertexBuffer = renderer.createBuffer(
		vertexBufferSize,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.copyBuffer(vertexStagingBuffer, m_vertexBuffer, vertexBufferSize);
	renderer.destroyBuffer(vertexStagingBuffer);

	auto indexBufferSize = m_indices.size() * sizeof(uint32_t);
	auto indexStagingBuffer = renderer.createBuffer(
		indexBufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(indexStagingBuffer, m_indices.data(), indexBufferSize);

	m_indexBuffer = renderer.createBuffer(
		indexBufferSize,
		VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.copyBuffer(indexStagingBuffer, m_indexBuffer, indexBufferSize);
	renderer.destroyBuffer(indexStagingBuffer);
}

void GFXEngine::Graphics::PositionMesh::destroy(Renderer & renderer)
{
	renderer.destroyBuffer(m_vertexBuffer);
	renderer.destroyBuffer(m_indexBuffer);
}

Math::AABB GFXEngine::Graphics::PositionMesh::computeAABB() const
{
	auto min = glm::vec3(std::numeric_limits<float>::max());
	auto max = glm::vec3(std::numeric_limits<float>::lowest());

	for (const auto& vertex : m_vertices) {
		min = glm::min(min, vertex.pos);
		max = glm::max(max, vertex.pos);
	}

	return Math::AABB(min, max);
}

const LibGFX::Buffer& GFXEngine::Graphics::PositionMesh::getVertexBuffer() const
{
	return m_vertexBuffer;
}

const LibGFX::Buffer& GFXEngine::Graphics::PositionMesh::getIndexBuffer() const
{
	return m_indexBuffer;
}

size_t GFXEngine::Graphics::PositionMesh::getIndexCount() const
{
	return m_indices.size();
}

GFXEngine::EngineTypes::VertexComponentView GFXEngine::Graphics::PositionMesh::getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const
{
	if (!m_vertices.empty())
	{
		switch (component)
		{
		case GFXEngine::EngineTypes::VertexComponent::Position:
			return {
				.data = &m_vertices[0].pos,
				.count = m_vertices.size(),
				.stride = sizeof(PositionVertex),
				.type = typeid(glm::vec3)
			};
		default:
			return EngineTypes::VertexComponentView::empty();
		}
	}
	return EngineTypes::VertexComponentView::empty();
}

MeshVertexPointer GFXEngine::Graphics::PositionMesh::getVertexPointer() const
{
	return {
		.vertexData = m_vertices.data(),
		.vertexCount = m_vertices.size(),
		.vertexStride = sizeof(PositionVertex),
		.vertexType = typeid(PositionVertex)
	};
}

std::span<const uint32_t> GFXEngine::Graphics::PositionMesh::getIndices() const
{
	return m_indices;
}