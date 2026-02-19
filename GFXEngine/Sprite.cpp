#include "Sprite.h"
#include "Utils.h"
#include "Shapes.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;
using namespace GFXEngine::Core;
using namespace GFXEngine::Math;

void GFXEngine::Core::Sprite::init(GFXEngine::Graphics::Renderer& renderer)
{
	LibGFX::ImageData imageData = Utils::loadImage(m_texturePath);
	m_texture = renderer.loadTexture(imageData);

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
	std::vector<VkDescriptorSet> descriptorSets = {
		camera.getDescriptorSet(imageIndex),
		m_textureDescriptorSet
	};
	renderer.usePipeline(m_pipeline, imageIndex);
	renderer.bindDescriptorSets(descriptorSets, m_pipeline.getPipelineLayout(), imageIndex);
	renderer.bindPushConstants(&model, sizeof(glm::mat4), m_pipeline.getPipelineLayout(), imageIndex);
	renderer.drawBuffers(m_vertexBuffer, m_indexBuffer, static_cast<uint32_t>(m_indices.size()), imageIndex);
}

void GFXEngine::Core::Sprite::destroy(GFXEngine::Graphics::Renderer& renderer)
{
	renderer.disposeTexture(m_texture);
	renderer.destroyBuffer(m_vertexBuffer);
	renderer.destroyBuffer(m_indexBuffer);
}

void Sprite::createDescriptorSet(GFXEngine::Graphics::Renderer& renderer, VkDescriptorSetLayout descriptorSetLayout)
{
	m_textureDescriptorSet = renderer.allocateTextureDescriptorSet(m_texture, 0, descriptorSetLayout);
}
