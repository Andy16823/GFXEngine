#include "Mesh3D.h"

void GFXEngine::Graphics::Mesh3D::init(Renderer& renderer)
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

void GFXEngine::Graphics::Mesh3D::destroy(Renderer& renderer)
{
	renderer.destroyBuffer(m_vertexBuffer);
	renderer.destroyBuffer(m_indexBuffer);
}

GFXEngine::Math::AABB GFXEngine::Graphics::Mesh3D::computeAABB() const
{
	Math::AABB aabb;
	for (const auto& vertex : m_vertices) {
		aabb = aabb.unionWith(Math::AABB(vertex.pos, vertex.pos));
	}
	return aabb;
}

GFXEngine::Graphics::MeshVertexPointer GFXEngine::Graphics::Mesh3D::getVertexPointer() const
{
	MeshVertexPointer pointer{
		.vertexData = m_vertices.data(),
		.vertexCount = m_vertices.size(),
		.vertexStride = sizeof(EngineTypes::Vertex3D),
		.vertexType = typeid(EngineTypes::Vertex3D)
	};
	return pointer;
}

GFXEngine::EngineTypes::VertexComponentView GFXEngine::Graphics::Mesh3D::getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const
{
	if (!m_vertices.empty())
	{
		switch (component)
		{
		case GFXEngine::EngineTypes::VertexComponent::Position:
			return {
				.data = &m_vertices[0].pos,
				.count = m_vertices.size(),
				.stride = sizeof(EngineTypes::Vertex3D),
				.type = typeid(glm::vec3)
			};
			break;
		case GFXEngine::EngineTypes::VertexComponent::Color:
			return {
				.data = &m_vertices[0].color,
				.count = m_vertices.size(),
				.stride = sizeof(EngineTypes::Vertex3D),
				.type = typeid(glm::vec3)
			};
			break;
		case GFXEngine::EngineTypes::VertexComponent::TexCoord:
			return {
				.data = &m_vertices[0].texCoord,
				.count = m_vertices.size(),
				.stride = sizeof(EngineTypes::Vertex3D),
				.type = typeid(glm::vec2)
			};
			break;
		case GFXEngine::EngineTypes::VertexComponent::Normal:
			return {
				.data = &m_vertices[0].normal,
				.count = m_vertices.size(),
				.stride = sizeof(EngineTypes::Vertex3D),
				.type = typeid(glm::vec3)
			};
			break;
		case GFXEngine::EngineTypes::VertexComponent::Tangent:
			return {
				.data = &m_vertices[0].tangent,
				.count = m_vertices.size(),
				.stride = sizeof(EngineTypes::Vertex3D),
				.type = typeid(glm::vec4)
			};
			break;
		default:
			return GFXEngine::EngineTypes::VertexComponentView::empty();
			break;
		}
	}
	return GFXEngine::EngineTypes::VertexComponentView::empty();
}
