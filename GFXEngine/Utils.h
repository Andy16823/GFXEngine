#pragma once
#include <string>
#include "Imaging.h"
#include "Renderer.h"
#include "Camera3D.h"
#include <vector>
#include <utility>
#include "Mesh.h"
#include "UnlitMaterial.h"
#include "PBRMaterial.h"
#include "GeometryPipeline.h"

namespace GFXEngine {

	/// <summary>
	/// Utility class that provides static functions for common tasks such as loading images, creating solid color textures, creating uniform buffers for cameras, and loading meshes and materials from files.
	/// </summary>
	class Utils
	{
	public:
		static LibGFX::ImageData loadImage(const std::string& filePath, bool flipVertically = true);
		static LibGFX::ImageData createSolidColorImage(uint32_t width, uint32_t height, const glm::vec4& color);
		static LibGFX::CubemapData loadCubemap(const std::vector<std::string>& filePaths, bool flipVertically = true);
		static std::pair<std::vector<LibGFX::Buffer>, std::vector<VkDescriptorSet>> createCameraUniformBuffers(Graphics::Renderer& renderer, const GFXEngine::Graphics::Camera3D& camera, VkDescriptorSetLayout descriptorSetLayout);
		static std::vector<GFXEngine::Graphics::Mesh> loadMeshesFromFile(const std::string& filePath);
		static std::vector<GFXEngine::Graphics::UnlitMaterial> loadMaterialsFromFile(const std::string& filePath);
		static std::vector<GFXEngine::Graphics::PBRMaterial> loadPBRMaterialsFromFile(const std::string& filePath);
		static std::string getBasePath(const std::string& filePath);
		static std::string getFileName(const std::string& filePath);
		static bool isAbsolutePath(const std::string& filePath);
		static void log(const std::string& service, const std::string& message);
	};
}
