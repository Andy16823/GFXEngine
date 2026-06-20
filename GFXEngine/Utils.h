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

	class Utils
	{
	public:
		//************************************
		// Method:    loadImage
		// FullName:  GFXEngine::Utils::loadImage
		// Access:    public static 
		// Returns:   LibGFX::ImageData
		// Qualifier:
		// Parameter: const std::string & filePath
		// Parameter: bool flipVertically
		//************************************
		static LibGFX::ImageData loadImage(const std::string& filePath, bool flipVertically = true);
		
		//************************************
		// Method:    createSolidColorImage
		// FullName:  GFXEngine::Utils::createSolidColorImage
		// Access:    public static 
		// Returns:   LibGFX::ImageData
		// Qualifier:
		// Parameter: uint32_t width
		// Parameter: uint32_t height
		// Parameter: const glm::vec4 & color
		//************************************
		static LibGFX::ImageData createSolidColorImage(uint32_t width, uint32_t height, const glm::vec4& color);
		
		//************************************
		// Method:    loadCubemap
		// FullName:  GFXEngine::Utils::loadCubemap
		// Access:    public static 
		// Returns:   LibGFX::CubemapData
		// Qualifier:
		// Parameter: const std::vector<std::string> & filePaths
		// Parameter: bool flipVertically
		//************************************
		static LibGFX::CubemapData loadCubemap(const std::vector<std::string>& filePaths, bool flipVertically = true);

		//************************************
		// Method:    createCameraUniformBuffers
		// FullName:  GFXEngine::Utils::createCameraUniformBuffers
		// Access:    public static 
		// Returns:   std::pair<std::vector<LibGFX::Buffer>, std::vector<VkDescriptorSet>>
		// Qualifier:
		// Parameter: Graphics::Renderer & renderer
		// Parameter: const GFXEngine::Graphics::Camera3D & camera
		// Parameter: VkDescriptorSetLayout descriptorSetLayout
		//************************************
		static std::pair<std::vector<LibGFX::Buffer>, std::vector<VkDescriptorSet>> createCameraUniformBuffers(Graphics::Renderer& renderer, const GFXEngine::Graphics::Camera3D& camera, VkDescriptorSetLayout descriptorSetLayout);
		
		//************************************
		// Method:    loadMeshesFromFile
		// FullName:  GFXEngine::Utils::loadMeshesFromFile
		// Access:    public static 
		// Returns:   std::vector<GFXEngine::Graphics::Mesh3D>
		// Qualifier:
		// Parameter: const std::string & filePath
		//************************************
		static std::vector<GFXEngine::Graphics::Mesh3D> loadMeshesFromFile(const std::string& filePath);
		
		//************************************
		// Method:    loadMaterialsFromFile
		// FullName:  GFXEngine::Utils::loadMaterialsFromFile
		// Access:    public static 
		// Returns:   std::vector<GFXEngine::Graphics::UnlitMaterial>
		// Qualifier:
		// Parameter: const std::string & filePath
		//************************************
		static std::vector<GFXEngine::Graphics::UnlitMaterial> loadMaterialsFromFile(const std::string& filePath);
		
		//************************************
		// Method:    loadPBRMaterialsFromFile
		// FullName:  GFXEngine::Utils::loadPBRMaterialsFromFile
		// Access:    public static 
		// Returns:   std::vector<GFXEngine::Graphics::PBRMaterial>
		// Qualifier:
		// Parameter: const std::string & filePath
		//************************************
		static std::vector<GFXEngine::Graphics::PBRMaterial> loadPBRMaterialsFromFile(const std::string& filePath);
		
		//************************************
		// Method:    getBasePath
		// FullName:  GFXEngine::Utils::getBasePath
		// Access:    public static 
		// Returns:   std::filesystem::path
		// Qualifier:
		// Parameter: const std::filesystem::path & filePath
		//************************************
		static std::filesystem::path getBasePath(const std::filesystem::path& filePath);
		
		//************************************
		// Method:    getBasePath
		// FullName:  GFXEngine::Utils::getBasePath
		// Access:    public static 
		// Returns:   std::string
		// Qualifier:
		// Parameter: const std::string & filePath
		//************************************
		static std::string getBasePath(const std::string& filePath);
		
		//************************************
		// Method:    getFileName
		// FullName:  GFXEngine::Utils::getFileName
		// Access:    public static 
		// Returns:   std::string
		// Qualifier:
		// Parameter: const std::string & filePath
		//************************************
		static std::string getFileName(const std::string& filePath);
		
		//************************************
		// Method:    generateUUID
		// FullName:  GFXEngine::Utils::generateUUID
		// Access:    public static 
		// Returns:   std::string
		// Qualifier:
		//************************************
		static std::string generateUUID();
		
		//************************************
		// Method:    fileExists
		// FullName:  GFXEngine::Utils::fileExists
		// Access:    public static 
		// Returns:   bool
		// Qualifier:
		// Parameter: const std::string & filePath
		//************************************
		static bool fileExists(const std::string& filePath);
		
		//************************************
		// Method:    isAbsolutePath
		// FullName:  GFXEngine::Utils::isAbsolutePath
		// Access:    public static 
		// Returns:   bool
		// Qualifier:
		// Parameter: const std::string & filePath
		//************************************
		static bool isAbsolutePath(const std::string& filePath);
		
		//************************************
		// Method:    log
		// FullName:  GFXEngine::Utils::log
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & service
		// Parameter: const std::string & message
		//************************************
		static void log(const std::string& service, const std::string& message);
		
		//************************************
		// Method:    saveJsonToFile
		// FullName:  GFXEngine::Utils::saveJsonToFile
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: const nlohmann::json & jsonData
		// Parameter: const std::string & filename
		//************************************
		static void saveJsonToFile(const nlohmann::json& jsonData, const std::string& filename);
		
		//************************************
		// Method:    createFile
		// FullName:  GFXEngine::Utils::createFile
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & filename
		//************************************
		static void createFile(const std::string& filename);
		
		//************************************
		// Method:    createDirectory
		// FullName:  GFXEngine::Utils::createDirectory
		// Access:    public static 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & directoryPath
		//************************************
		static void createDirectory(const std::string& directoryPath);
		
		//************************************
		// Method:    loadJsonFromFile
		// FullName:  GFXEngine::Utils::loadJsonFromFile
		// Access:    public static 
		// Returns:   nlohmann::json
		// Qualifier:
		// Parameter: const std::string & filename
		//************************************
		static nlohmann::json loadJsonFromFile(const std::string& filename);
		
		//************************************
		// Method:    serializeMat4
		// FullName:  GFXEngine::Utils::serializeMat4
		// Access:    public static 
		// Returns:   nlohmann::json
		// Qualifier:
		// Parameter: const glm::mat4 & matrix
		//************************************
		static nlohmann::json serializeMat4(const glm::mat4& matrix);
		
		//************************************
		// Method:    serializeVec2
		// FullName:  GFXEngine::Utils::serializeVec2
		// Access:    public static 
		// Returns:   nlohmann::json
		// Qualifier:
		// Parameter: const glm::vec2 & vector
		//************************************
		static nlohmann::json serializeVec2(const glm::vec2& vector);
		
		//************************************
		// Method:    serializeVec3
		// FullName:  GFXEngine::Utils::serializeVec3
		// Access:    public static 
		// Returns:   nlohmann::json
		// Qualifier:
		// Parameter: const glm::vec3 & vector
		//************************************
		static nlohmann::json serializeVec3(const glm::vec3& vector);
		
		//************************************
		// Method:    serializeVec4
		// FullName:  GFXEngine::Utils::serializeVec4
		// Access:    public static 
		// Returns:   nlohmann::json
		// Qualifier:
		// Parameter: const glm::vec4 & vector
		//************************************
		static nlohmann::json serializeVec4(const glm::vec4& vector);
		
		//************************************
		// Method:    serializeQuat
		// FullName:  GFXEngine::Utils::serializeQuat
		// Access:    public static 
		// Returns:   nlohmann::json
		// Qualifier:
		// Parameter: const glm::quat & quat
		//************************************
		static nlohmann::json serializeQuat(const glm::quat& quat);

		//************************************
		// Method:    deserializeMat4
		// FullName:  GFXEngine::Utils::deserializeMat4
		// Access:    public static 
		// Returns:   glm::mat4
		// Qualifier:
		// Parameter: const nlohmann::json & jsonData
		//************************************
		static glm::mat4 deserializeMat4(const nlohmann::json& jsonData);
		
		//************************************
		// Method:    deserializeVec2
		// FullName:  GFXEngine::Utils::deserializeVec2
		// Access:    public static 
		// Returns:   glm::vec2
		// Qualifier:
		// Parameter: const nlohmann::json & jsonData
		//************************************
		static glm::vec2 deserializeVec2(const nlohmann::json& jsonData);
		
		//************************************
		// Method:    deserializeVec3
		// FullName:  GFXEngine::Utils::deserializeVec3
		// Access:    public static 
		// Returns:   glm::vec3
		// Qualifier:
		// Parameter: const nlohmann::json & jsonData
		//************************************
		static glm::vec3 deserializeVec3(const nlohmann::json& jsonData);
		
		//************************************
		// Method:    deserializeVec4
		// FullName:  GFXEngine::Utils::deserializeVec4
		// Access:    public static 
		// Returns:   glm::vec4
		// Qualifier:
		// Parameter: const nlohmann::json & jsonData
		//************************************
		static glm::vec4 deserializeVec4(const nlohmann::json& jsonData);
		
		//************************************
		// Method:    deserializeQuat
		// FullName:  GFXEngine::Utils::deserializeQuat
		// Access:    public static 
		// Returns:   glm::quat
		// Qualifier:
		// Parameter: const nlohmann::json & jsonData
		//************************************
		static glm::quat deserializeQuat(const nlohmann::json& jsonData);
	};
}
