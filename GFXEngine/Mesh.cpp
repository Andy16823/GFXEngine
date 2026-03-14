#include "Mesh.h"

void GFXEngine::Graphics::Mesh::init(Renderer& renderer)
{
	// TODO: Currently using rebar buffers for simplicity, but we should eventually switch to staging buffers for fallback support on devices that don't support rebar buffers
	size_t vertexBufferSize = m_vertices.size() * sizeof(EngineTypes::Vertex3D);
	m_vertexBuffer = renderer.createBuffer(vertexBufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(m_vertexBuffer, m_vertices.data(), m_vertices.size(), false);

	size_t indexBufferSize = m_indices.size() * sizeof(uint32_t);
	m_indexBuffer = renderer.createBuffer(indexBufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(m_indexBuffer, m_indices.data(), m_indices.size(), false);
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
