#include "Mesh2D.h"

using namespace GFXEngine;
using namespace GFXEngine::EngineTypes;
using namespace GFXEngine::Graphics;

void GFXEngine::Graphics::Mesh2D::init(Renderer& renderer)
{
	auto vertexBufferSize = m_vertices.size() * sizeof(Vertex2D);

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

	auto indexBufferSize = m_indices.size() * sizeof(uint32_t);

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

void GFXEngine::Graphics::Mesh2D::destroy(Renderer& renderer)
{
	renderer.destroyBuffer(m_vertexBuffer);
	renderer.destroyBuffer(m_indexBuffer);
}

GFXEngine::Math::AABB GFXEngine::Graphics::Mesh2D::computeAABB() const
{
	GFXEngine::Math::AABB aabb;
	for (const auto& vert : m_vertices) {
		aabb = aabb.unionWith(GFXEngine::Math::AABB(vert.pos, vert.pos));
	}
	return aabb;
}

const LibGFX::Buffer& GFXEngine::Graphics::Mesh2D::getVertexBuffer() const
{
	return m_vertexBuffer;
}

const LibGFX::Buffer& GFXEngine::Graphics::Mesh2D::getIndexBuffer() const
{
	return m_indexBuffer;
}

size_t GFXEngine::Graphics::Mesh2D::getIndexCount() const
{
	return m_indices.size();
}

GFXEngine::EngineTypes::VertexComponentView GFXEngine::Graphics::Mesh2D::getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const
{
	if (!m_vertices.empty()) {
		switch (component)
		{
		case GFXEngine::EngineTypes::VertexComponent::Position:
			return {
				.data = &m_vertices[0].pos,
				.count = m_vertices.size(),
				.stride = sizeof(Vertex2D),
				.type = typeid(glm::vec3)
			};
		case GFXEngine::EngineTypes::VertexComponent::Color:
			return {
				.data = &m_vertices[0].color,
				.count = m_vertices.size(),
				.stride = sizeof(Vertex2D),
				.type = typeid(glm::vec3)
			};
		case GFXEngine::EngineTypes::VertexComponent::TexCoord:
			return {
				.data = &m_vertices[0].texCoord,
				.count = m_vertices.size(),
				.stride = sizeof(Vertex2D),
				.type = typeid(glm::vec2)
			};
		default:
			return VertexComponentView::empty();
		}
	}
	return VertexComponentView::empty();
}

GFXEngine::Graphics::MeshVertexPointer GFXEngine::Graphics::Mesh2D::getVertexPointer() const
{
	return {
		.vertexData = m_vertices.data(),
		.vertexCount = m_vertices.size(),
		.vertexStride = sizeof(Vertex2D),
		.vertexType = typeid(Vertex2D)
	};
}

std::span<const uint32_t> GFXEngine::Graphics::Mesh2D::getIndices() const
{
	return m_indices;
}