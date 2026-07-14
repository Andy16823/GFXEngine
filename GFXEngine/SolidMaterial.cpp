#include "SolidMaterial.h"

void GFXEngine::Graphics::SolidMaterial::init(Renderer& renderer)
{
	VkDeviceSize bufferSize = sizeof(glm::vec4);
	m_buffer = renderer.createBuffer(
		bufferSize,
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(m_buffer, &m_color, sizeof(glm::vec4));
	m_decriptorSet = renderer.allocateUniformBufferDescriptorSet(m_buffer, 0, renderer.getUniformBufferLayout());
}

void GFXEngine::Graphics::SolidMaterial::destroy(Renderer & renderer)
{
	renderer.destroyBuffer(m_buffer);
	renderer.freeUniformBufferDescriptorSet(m_decriptorSet);
}
