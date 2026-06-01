#include "Fog.h"
#include "DataTypes.h"
#include <cassert>

void GFXEngine::Graphics::Fog::init(Renderer& renderer)
{
	size_t swapchainImageCount = renderer.getSwapchainImageCount();
	m_uniformBuffers.reserve(swapchainImageCount);
	m_descriptorSets.reserve(swapchainImageCount);

	VkDeviceSize bufferSize = sizeof(EngineTypes::LinearFogData);
	static_assert(sizeof(EngineTypes::LinearFogData) % 16 == 0, "LinearFogData must be a multiple of 16 bytes to ensure proper alignment in the uniform buffer.");

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

void GFXEngine::Graphics::Fog::update(Renderer& renderer, const Camera& camera, uint32_t imageIndex)
{
	glm::vec4 fogParams = glm::vec4(minDistance, maxDistance, density, 0.0f);
	EngineTypes::LinearFogData fogData = {
		.color = color,
		.fogParams = fogParams
	};
	renderer.updateBuffer(m_uniformBuffers[imageIndex], &fogData, sizeof(fogData));
}

void GFXEngine::Graphics::Fog::destroy(Renderer& renderer)
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

nlohmann::json GFXEngine::Graphics::Fog::serialize() const
{
	nlohmann::json data;
	data["density"] = density;
	data["minDistance"] = minDistance;
	data["maxDistance"] = maxDistance;
	data["color"] = { color.r, color.g, color.b, color.a };
	return data;
}

void GFXEngine::Graphics::Fog::deserialize(const nlohmann::json& data, SerializationContext& context, SerializationFlags flags /*= SerializationFlags::None*/)
{
	density = data.value("density", density);
	minDistance = data.value("minDistance", minDistance);
	maxDistance = data.value("maxDistance", maxDistance);
	if (data.contains("color") && data["color"].is_array() && data["color"].size() == 4) {
		color = glm::vec4(
			data["color"][0].get<float>(),
			data["color"][1].get<float>(),
			data["color"][2].get<float>(),
			data["color"][3].get<float>()
		);
	}
}
