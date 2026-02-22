#pragma once
#include <string>
#include "Imaging.h"
#include "Renderer.h"
#include "Camera3D.h"
#include <vector>
#include <utility>
#include "Mesh.h"
#include "UnlitMaterial.h"
#include "GeometryPipeline.h"

namespace GFXEngine {
	class Utils
	{
	public:
		static LibGFX::ImageData loadImage(const std::string& filePath, bool flipVertically = true);
		static LibGFX::ImageData createSolidColorImage(uint32_t width, uint32_t height, const glm::vec4& color);
		static std::pair<std::vector<LibGFX::Buffer>, std::vector<VkDescriptorSet>> createCameraUniformBuffers(Graphics::Renderer& renderer, const GFXEngine::Graphics::Camera3D& camera, VkDescriptorSetLayout descriptorSetLayout);
		static std::vector<GFXEngine::Graphics::Mesh> loadMeshesFromFile(const std::string& filePath);
		static std::vector<GFXEngine::Graphics::UnlitMaterial> loadMaterialsFromFile(const std::string& filePath, const GFXEngine::Graphics::GeometryPipeline& pipeline);
		static std::string getBasePath(const std::string& filePath);
		static std::string getFileName(const std::string& filePath);
		static bool isAbsolutePath(const std::string& filePath);
	};
}
