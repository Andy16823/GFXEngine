#pragma once
#include <string>
#include "Imaging.h"
#include "Renderer.h"
#include "Camera3D.h"
#include <vector>
#include <utility>

namespace GFXEngine {
	class Utils
	{
	public:
		static LibGFX::ImageData loadImage(const std::string& filePath);
		static std::pair<std::vector<LibGFX::Buffer>, std::vector<VkDescriptorSet>> createCameraUniformBuffers(Graphics::Renderer& renderer, const GFXEngine::Graphics::Camera3D& camera, VkDescriptorSetLayout descriptorSetLayout);
	};
}
