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

void DirectionalLight::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags)
{
	direction = glm::vec3(data["direction"][0], data["direction"][1], data["direction"][2]);
	color = glm::vec3(data["color"][0], data["color"][1], data["color"][2]);
	intensity = data["intensity"].get<float>();
}

nlohmann::json DirectionalLight::serialize() const
{
	nlohmann::json data;
	data["direction"] = { direction.x, direction.y, direction.z };
	data["color"] = { color.r, color.g, color.b };
	data["intensity"] = intensity;
	return data;
}

void DirectionalLight::destroy(Renderer& renderer)
{
	for (auto& buffer : m_uniformBuffers) {
		renderer.destroyBuffer(buffer);
	}
	m_uniformBuffers.clear();

	for (auto& descriptorSet : m_descriptorSets) {
		renderer.freeUniformBufferDescriptorSet(descriptorSet);
	}
	m_descriptorSets.clear();
}

void DirectionalLight::update(Renderer& renderer, const Camera& camera, uint32_t imageIndex)
{
	EngineTypes::DirectionalLightData lightData = {
		.direction = glm::vec4(glm::normalize(direction), 0.0f),
		.color = glm::vec4(color, intensity)
	};

	renderer.updateBuffer(m_uniformBuffers[imageIndex], &lightData, sizeof(lightData));
}