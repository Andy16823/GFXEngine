#include "EnviromentMap.h"
#include "Shapes.h"
#include "DataTypes.h"
#include "EngineDefinitions.h"
#include "Utils.h"
#include "RenderTask.h"
#include "RenderQueue.h"

using namespace GFXEngine::Graphics;

EnviromentMap::EnviromentMap(const std::string& name, const std::vector<std::string>& faceFilepaths) : Asset(name)
{
	auto [vertices, indices] = Graphics::Shapes::createSkybox();
	m_mesh = std::make_unique<PositionMesh>();
	m_mesh->setVertices(std::move(vertices));
	m_mesh->setIndices(std::move(indices));

	m_envMaterial = std::make_unique<EnviromentMaterial>();
	LibGFX::CubemapData cubemapData = GFXEngine::Utils::loadCubemap(faceFilepaths, false);
	m_envMaterial->setCubemapData(std::move(cubemapData));
}

EnviromentMap::EnviromentMap(const std::string& name, const std::filesystem::path& filePath) : Asset(name)
{
	nlohmann::json data = GFXEngine::Utils::loadJsonFromFile(filePath.string());
	if (!data.contains("faces") || !data["faces"].is_array() || data["faces"].size() != 6) {
		throw std::runtime_error("EnviromentMap JSON data must contain a 'faces' array with 6 file paths.");
	}

	// Load optional parameters with default values
	horizonFactor = data.value("horizonFactor", 1.0f);
	horizonFogExponent = data.value("horizonFogExponent", 1.5f);

	// Create the mesh for the skybox
	auto [vertices, indices] = Graphics::Shapes::createSkybox();
	m_mesh = std::make_unique<PositionMesh>();
	m_mesh->setVertices(std::move(vertices));
	m_mesh->setIndices(std::move(indices));

	// Load cubemap textures
	std::filesystem::path basePath = GFXEngine::Utils::getBasePath(filePath);
	std::vector<std::string> faceFilepaths;
	for (const auto& face : data["faces"]) {
		auto faceStr = face.get<std::string>();
		auto fullPath = basePath / faceStr;
		faceFilepaths.push_back(fullPath.string());
	}

	// Create the material and set the cubemap data
	m_envMaterial = std::make_unique<EnviromentMaterial>();
	LibGFX::CubemapData cubemapData = GFXEngine::Utils::loadCubemap(faceFilepaths, false);
	m_envMaterial->setCubemapData(std::move(cubemapData));
}

void EnviromentMap::init(GFXEngine::Graphics::Renderer& renderer)
{
	m_mesh->init(renderer);
	m_envMaterial->init(renderer);

	// Create uniform buffers and descriptor sets for each swapchain image
	size_t swapchainImageCount = renderer.getSwapchainImageCount();
	VkDeviceSize bufferSize = sizeof(GFXEngine::EngineTypes::EnviromentMapData);
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

		// Update after creating the buffer to ensure it has the correct initial data
		this->updateUniformBuffer(renderer, i);
	}

}

void EnviromentMap::update(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	this->updateUniformBuffer(renderer, imageIndex);
}

void EnviromentMap::destroy(GFXEngine::Graphics::Renderer& renderer)
{
	m_mesh->destroy(renderer);
	m_envMaterial->destroy(renderer);

	for (auto& buffer : m_uniformBuffers) {
		renderer.destroyBuffer(buffer);
	}
	m_uniformBuffers.clear();

	for (auto& descriptorSet : m_descriptorSets) {
		renderer.freeUniformBufferDescriptorSet(descriptorSet);
	}
	m_descriptorSets.clear();
}

void EnviromentMap::updateUniformBuffer(Renderer& renderer, uint32_t imageIndex)
{
	EngineTypes::EnviromentMapData envData = {
		.parameters = glm::vec4(horizonFactor, horizonFogExponent, 0.0f, 0.0f)
	};
	renderer.updateBuffer(m_uniformBuffers[imageIndex], &envData, sizeof(envData));
}
