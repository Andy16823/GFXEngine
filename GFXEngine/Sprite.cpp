#include "Sprite.h"
#include "Utils.h"
#include "Shapes.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;
using namespace GFXEngine::Core;
using namespace GFXEngine::Math;

void GFXEngine::Core::Sprite::init(GFXEngine::Graphics::Renderer& renderer)
{
	Shapes::createSprite(m_vertices, m_indices);

	size_t vertexBufferSize = m_vertices.size() * sizeof(EngineTypes::Vertex3D);
	m_vertexBuffer = renderer.createBuffer(vertexBufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(m_vertexBuffer, m_vertices.data(), m_vertices.size());

	size_t indexBufferSize = m_indices.size() * sizeof(uint32_t);
	m_indexBuffer = renderer.createBuffer(indexBufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(m_indexBuffer, m_indices.data(), m_indices.size());
}

void GFXEngine::Core::Sprite::update(float deltaTime)
{

}

void GFXEngine::Core::Sprite::render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera3D& camera, uint32_t imageIndex)
{
	glm::mat4 model = transform.getModelMatrix();
	m_material.bind(renderer, camera, imageIndex);
	renderer.bindPushConstants(&model, sizeof(glm::mat4), m_material.getPipelineLayout(), imageIndex);
	renderer.drawBuffers(m_vertexBuffer, m_indexBuffer, static_cast<uint32_t>(m_indices.size()), imageIndex);
}

void GFXEngine::Core::Sprite::destroy(GFXEngine::Graphics::Renderer& renderer)
{
	renderer.destroyBuffer(m_vertexBuffer);
	renderer.destroyBuffer(m_indexBuffer);
}