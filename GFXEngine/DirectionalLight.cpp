#include "DirectionalLight.h"

using namespace GFXEngine::Graphics;

void GFXEngine::Graphics::DirectionalLight::init(Renderer& renderer)
{
	uint32_t swapchainImageCount = renderer.getSwapchainImageCount();
	VkDeviceSize bufferSize = sizeof(EngineTypes::DirectionalLightData);
	m_uniformBuffers.reserve(swapchainImageCount);
	m_descriptorSets.reserve(swapchainImageCount);
	for (size_t i = 0; i < swapchainImageCount; i++) {
		LibGFX::Buffer uniformBuffer = renderer.createBuffer(
			bufferSize,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		);
		VkDescriptorSet descriptorSet = renderer.allocateUniformBufferDescriptorSet(uniformBuffer, 0, renderer.getUniformBufferLayout());
		m_uniformBuffers.push_back(std::move(uniformBuffer));
		m_descriptorSets.push_back(descriptorSet);
	}
}

void DirectionalLight::destroy(Renderer& renderer)
{
	for (auto& buffer : m_uniformBuffers) {
		renderer.destroyBuffer(buffer);
	}
}

void DirectionalLight::bind(Renderer& renderer, const Camera& camera, const LibGFX::Pipeline& pipeline, uint32_t firstSet, uint32_t imageIndex) const
{
	auto descriptorSet = m_descriptorSets[imageIndex];
	renderer.bindDescriptorSet(descriptorSet, pipeline.getPipelineLayout(), firstSet, imageIndex);
}

void DirectionalLight::update(Renderer& renderer, const Camera& camera, uint32_t imageIndex)
{
	EngineTypes::DirectionalLightData lightData = {
		.direction = glm::vec4(glm::normalize(direction), 0.0f),
		.color = glm::vec4(color, intensity)
	};

	renderer.updateBuffer(m_uniformBuffers[imageIndex], &lightData, sizeof(lightData));
}
