#pragma once
#include <string>
#include "Imaging.h"
#include "Renderer.h"
#include "Camera3D.h"
#include <vector>
#include <utility>
#include "Mesh3D.h"
#include "UnlitMaterial.h"
#include "PBRMaterial.h"
#include <nlohmann/json.hpp>

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
		static std::vector<GFXEngine::Graphics::Mesh3D> loadMeshesFromFile(const std::string& filePath);
		static std::vector<GFXEngine::Graphics::UnlitMaterial> loadMaterialsFromFile(const std::string& filePath);
		static std::vector<GFXEngine::Graphics::PBRMaterial> loadPBRMaterialsFromFile(const std::string& filePath);
		static std::filesystem::path getBasePath(const std::filesystem::path& filePath);
		static std::string getBasePath(const std::string& filePath);
		static std::string getFileName(const std::string& filePath);
		static std::string generateUUID();
		static bool fileExists(const std::string& filePath);
		static bool isAbsolutePath(const std::string& filePath);
		static void log(const std::string& service, const std::string& message);
		static void saveJsonToFile(const nlohmann::json& jsonData, const std::string& filename);
		static nlohmann::json loadJsonFromFile(const std::string& filename);
		static nlohmann::json serializeMat4(const glm::mat4& matrix);
		static nlohmann::json serializeVec2(const glm::vec2& vector);
		static nlohmann::json serializeVec3(const glm::vec3& vector);
		static nlohmann::json serializeVec4(const glm::vec4& vector);
		static nlohmann::json serializeQuat(const glm::quat& quat);

		static glm::mat4 deserializeMat4(const nlohmann::json& jsonData);
		static glm::vec2 deserializeVec2(const nlohmann::json& jsonData);
		static glm::vec3 deserializeVec3(const nlohmann::json& jsonData);
		static glm::vec4 deserializeVec4(const nlohmann::json& jsonData);
		static glm::quat deserializeQuat(const nlohmann::json& jsonData);
	};
}
