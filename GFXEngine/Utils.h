#pragma once
#include <string>
#include "DataTypes.h"
#include "Imaging.h"
#include "Renderer.h"
#include "Camera3D.h"
#include <vector>
#include <utility>

// TODO: Move image loading in an own class. For now , this is a simple utility function to load an image from disk and return the pixel data along with the image dimensions and format. In the future, we can expand this to support more formats, error handling, and caching of loaded images if needed.
namespace GFXEngine {
	class Utils
	{
	public:
		static LibGFX::ImageData loadImage(const std::string& filePath);
		static std::pair<std::vector<LibGFX::Buffer>, std::vector<VkDescriptorSet>> createCameraUniformBuffers(Graphics::Renderer& renderer, const GFXEngine::Graphics::Camera3D& camera, VkDescriptorSetLayout descriptorSetLayout);
	};
}
