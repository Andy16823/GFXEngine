#include "Utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdexcept>

LibGFX::ImageData GFXEngine::Utils::loadImage(const std::string& filePath)
{
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(filePath.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	if (!pixels) {
		throw std::runtime_error("Failed to load texture image!");
	}
	LibGFX::ImageData imageData;
	imageData.pixels = pixels;
	imageData.width = static_cast<uint32_t>(texWidth);
	imageData.height = static_cast<uint32_t>(texHeight);
	imageData.format = VK_FORMAT_R8G8B8A8_UNORM;
	return imageData;
}

std::pair<std::vector<LibGFX::Buffer>, std::vector<VkDescriptorSet>> GFXEngine::Utils::createCameraUniformBuffers(Graphics::Renderer& renderer, const GFXEngine::Graphics::Camera3D& camera, VkDescriptorSetLayout descriptorSetLayout)
{
	size_t swapchainImageCount = renderer.getSwapchainImageCount();
	std::vector<LibGFX::Buffer> uniformBuffers(swapchainImageCount);
	std::vector<VkDescriptorSet> descriptorSets(swapchainImageCount);
	size_t bufferSize = sizeof(GFXEngine::EngineTypes::CameraBufferObject);

	for (size_t i = 0; i < swapchainImageCount; i++) {
		uniformBuffers[i] = renderer.createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		descriptorSets[i] = renderer.allocateUniformBufferDescriptorSet(uniformBuffers[i], 0, descriptorSetLayout);
	}
	return { uniformBuffers, descriptorSets };
}
