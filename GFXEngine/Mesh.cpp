#include "Mesh.h"

void GFXEngine::Graphics::Mesh::init(Renderer& renderer)
{
	// Create Vertex Buffer with staging buffer
	size_t vertexBufferSize = m_vertices.size() * sizeof(EngineTypes::Vertex3D);
	auto vertexStagingBuffer = renderer.createBuffer(
		vertexBufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(vertexStagingBuffer, m_vertices.data(), m_vertices.size());

	m_vertexBuffer = renderer.createBuffer(
		vertexBufferSize,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.copyBuffer(vertexStagingBuffer, m_vertexBuffer, vertexBufferSize);
	renderer.destroyBuffer(vertexStagingBuffer);

	// Create Index Buffer with staging buffer
	size_t indexBufferSize = m_indices.size() * sizeof(uint32_t);
	auto indexStagingBuffer = renderer.createBuffer(
		indexBufferSize,
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(indexStagingBuffer, m_indices.data(), m_indices.size());

	m_indexBuffer = renderer.createBuffer(
		indexBufferSize,
		VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.copyBuffer(indexStagingBuffer, m_indexBuffer, indexBufferSize);
	renderer.destroyBuffer(indexStagingBuffer);
}

void GFXEngine::Graphics::Mesh::draw(Renderer& renderer, uint32_t imageIndex) const
{
	renderer.drawBuffers(m_vertexBuffer, m_indexBuffer, m_indices.size(), imageIndex);
}

void GFXEngine::Graphics::Mesh::destroy(Renderer& renderer)
{
	renderer.destroyBuffer(m_vertexBuffer);
	renderer.destroyBuffer(m_indexBuffer);
}

GFXEngine::Math::AABB GFXEngine::Graphics::Mesh::computeAABB() const
{
	Math::AABB aabb;
	for (const auto& vertex : m_vertices) {
		aabb = aabb.unionWith(Math::AABB(vertex.pos, vertex.pos));
	}
	return aabb;
}
