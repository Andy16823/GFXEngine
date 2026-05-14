#include "Utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdexcept>
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/pbrmaterial.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <random>
#include <fstream>

LibGFX::ImageData GFXEngine::Utils::loadImage(const std::string& filePath, bool flipVertically)
{
	stbi_set_flip_vertically_on_load(flipVertically);
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(filePath.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	if (!pixels) {
		throw std::runtime_error("Failed to load texture image!");
	}
	LibGFX::ImageData imageData;
	imageData.width = static_cast<uint32_t>(texWidth);
	imageData.height = static_cast<uint32_t>(texHeight);
	imageData.format = VK_FORMAT_R8G8B8A8_UNORM;

	size_t imageSize = static_cast<size_t>(texWidth * texHeight * 4); // 4 bytes per pixel for RGBA
	imageData.pixels.resize(imageSize);
	std::memcpy(imageData.pixels.data(), pixels, imageSize);
	stbi_image_free(pixels);

	return imageData;
}

LibGFX::ImageData GFXEngine::Utils::createSolidColorImage(uint32_t width, uint32_t height, const glm::vec4& color)
{
	std::vector<uint8_t> pixels(width * height * 4);
	for (size_t i = 0; i < width * height; i++) {
		pixels[i * 4 + 0] = static_cast<uint8_t>(color.r * 255);
		pixels[i * 4 + 1] = static_cast<uint8_t>(color.g * 255);
		pixels[i * 4 + 2] = static_cast<uint8_t>(color.b * 255);
		pixels[i * 4 + 3] = static_cast<uint8_t>(color.a * 255);
	}
	LibGFX::ImageData imageData;
	imageData.pixels = std::move(pixels);
	imageData.width = width;
	imageData.height = height;
	imageData.format = VK_FORMAT_R8G8B8A8_UNORM;
	return imageData;
}

LibGFX::CubemapData GFXEngine::Utils::loadCubemap(const std::vector<std::string>& filePaths, bool flipVertically /*= true*/)
{
	if (filePaths.size() != 6) {
		throw std::runtime_error("Cubemap requires exactly 6 images!");
	}

	stbi_set_flip_vertically_on_load(flipVertically);

	LibGFX::CubemapData cubemapData;
	for (size_t i = 0; i < 6; i++) {
		int texWidth, texHeight, texChannels;
		stbi_uc* pixels = stbi_load(filePaths[i].c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		if (!pixels) {
			throw std::runtime_error("Failed to load cubemap image: " + filePaths[i]);
		}
		cubemapData.width = static_cast<uint32_t>(texWidth);
		cubemapData.height = static_cast<uint32_t>(texHeight);
		cubemapData.format = VK_FORMAT_R8G8B8A8_UNORM;

		size_t imageSize = static_cast<size_t>(texWidth * texHeight * 4); // 4 bytes per pixel for RGBA
		cubemapData.pixels[i].resize(imageSize);
		std::memcpy(cubemapData.pixels[i].data(), pixels, imageSize);
		stbi_image_free(pixels);
	}
	return cubemapData;
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

std::vector<GFXEngine::Graphics::Mesh> GFXEngine::Utils::loadMeshesFromFile(const std::string& filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		throw std::runtime_error("ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
	}
	std::vector<GFXEngine::Graphics::Mesh> meshes;

	for (size_t i = 0; i < scene->mNumMeshes; i++) {
		auto aiMesh = scene->mMeshes[i];

		std::vector<EngineTypes::Vertex3D> vertices(aiMesh->mNumVertices);
		for (size_t j = 0; j < aiMesh->mNumVertices; j++) {
			auto& aiVertex = aiMesh->mVertices[j];
			auto& aiNormal = aiMesh->mNormals[j];
			auto& aiTexCoord = aiMesh->mTextureCoords[0][j];
			auto& aiTangent = aiMesh->mTangents[j];
			auto& aiBitangent = aiMesh->mBitangents[j];

			glm::vec3 tangent = glm::vec3(aiTangent.x, aiTangent.y, aiTangent.z);
			glm::vec3 bitangent = glm::vec3(aiBitangent.x, aiBitangent.y, aiBitangent.z);
			glm::vec3 normal = glm::vec3(aiNormal.x, aiNormal.y, aiNormal.z);
			float handness = (glm::dot(glm::cross(normal, tangent), bitangent) < 0.0f) ? -1.0f : 1.0f;
			
			EngineTypes::Vertex3D vertex{};
			vertex.pos = glm::vec3(aiVertex.x, aiVertex.y, aiVertex.z);
			vertex.normal = normal;
			vertex.texCoord = glm::vec2(aiTexCoord.x, aiTexCoord.y);
			vertex.tangent = glm::vec4(tangent, handness);
			vertex.color = glm::vec3(1.0f);

			vertices[j] = vertex;
		}

		std::vector<uint32_t> indices;
		for (size_t j = 0; j < aiMesh->mNumFaces; j++) {
			auto& aiFace = aiMesh->mFaces[j];
			indices.insert(indices.end(), aiFace.mIndices, aiFace.mIndices + aiFace.mNumIndices);
		}

		GFXEngine::Graphics::Mesh mesh;
		mesh.setVertices(std::move(vertices));
		mesh.setIndices(std::move(indices));
		meshes.push_back(std::move(mesh));
	}
	return meshes;
}

std::vector<GFXEngine::Graphics::UnlitMaterial> GFXEngine::Utils::loadMaterialsFromFile(const std::string& filePath)
{
	auto basePath = getBasePath(filePath);

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		throw std::runtime_error("ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
	}

	std::vector<GFXEngine::Graphics::UnlitMaterial> materials;
	for (size_t i = 0; i < scene->mNumMaterials; i++) {
		auto aiMaterial = scene->mMaterials[i];
		aiString texturePath;
		if (aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
			std::string fullPath = basePath + texturePath.C_Str();
			materials.emplace_back(fullPath);
		} else {
			std::cerr << "Warning: Material " << i << " does not have a diffuse texture. Skipping." << std::endl;
		}
	}

	return materials;
}

std::vector<GFXEngine::Graphics::PBRMaterial> GFXEngine::Utils::loadPBRMaterialsFromFile(const std::string& filePath)
{
	auto basePath = getBasePath(filePath);

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		throw std::runtime_error("ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
	}

	std::vector<GFXEngine::Graphics::PBRMaterial> materials;
	materials.reserve(scene->mNumMaterials);

	for (size_t i = 0; i < scene->mNumMaterials; i++) {
		auto aiMaterial = scene->mMaterials[i];
		aiString albedoPath, normalPath, metallicRoughnessPath, aoPath;
		LibGFX::ImageData albedoData, normalData, metallicRoughnessData, aoData;

		if (aiMaterial->GetTexture(aiTextureType_BASE_COLOR, 0, &albedoPath) == AI_SUCCESS) {
			albedoData = loadImage(basePath + albedoPath.C_Str(), false);
		}
		else {
			albedoData = createSolidColorImage(1, 1, glm::vec4(1.0f));
		}

		if(aiMaterial->GetTexture(aiTextureType_NORMALS, 0, &normalPath) == AI_SUCCESS) {
			normalData = loadImage(basePath + normalPath.C_Str(), false);
		}
		else {
			normalData = createSolidColorImage(1, 1, glm::vec4(0.5f, 0.5f, 1.0f, 1.0f)); // Default normal map color
		}

		if (aiMaterial->GetTexture(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLICROUGHNESS_TEXTURE, &metallicRoughnessPath) == AI_SUCCESS) {
			metallicRoughnessData = loadImage(basePath + metallicRoughnessPath.C_Str(), false);
		}
		else {
			metallicRoughnessData = createSolidColorImage(1, 1, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)); // Default metallic-roughness map color
		}

		if (aiMaterial->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &aoPath) == AI_SUCCESS) {
			aoData = loadImage(basePath + aoPath.C_Str(), false);
		}
		else {
			aoData = createSolidColorImage(1, 1, glm::vec4(1.0f)); // Default AO map color
		}

		auto& pbrMaterial = materials.emplace_back();
		pbrMaterial.setAlbedoTexture(std::move(albedoData));
		pbrMaterial.setNormalTexture(std::move(normalData));
		pbrMaterial.setMetallicRoughnessTexture(std::move(metallicRoughnessData));
		pbrMaterial.setAOTexture(std::move(aoData));
	}

	return materials;
}

std::string GFXEngine::Utils::getBasePath(const std::string& filePath)
{
	size_t lastSlashPos = filePath.find_last_of("/\\");
	if (lastSlashPos == std::string::npos) {
		return ""; // No directory part in the path
	}
	return filePath.substr(0, lastSlashPos + 1);
}

std::string GFXEngine::Utils::getFileName(const std::string& filePath)
{
	size_t lastSlashPos = filePath.find_last_of("/\\");
	if (lastSlashPos == std::string::npos) {
		return filePath; // The entire path is the file name
	}
	return filePath.substr(lastSlashPos + 1);
}

std::string GFXEngine::Utils::generateUUID()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<uint32_t> dis;

	std::stringstream ss;

	ss << std::hex << std::setfill('0');

	ss << std::setw(8) << dis(gen) << "-";
	ss << std::setw(4) << (dis(gen) & 0xFFFF) << "-";
	ss << std::setw(4) << (dis(gen) & 0xFFFF) << "-";
	ss << std::setw(4) << (dis(gen) & 0xFFFF) << "-";
	ss << std::setw(12) << (
		(static_cast<uint64_t>(dis(gen)) << 32) | dis(gen)
		);

	return ss.str();
}

bool GFXEngine::Utils::fileExists(const std::string& filePath)
{
	std::ifstream file(filePath);
	return file.good();
}

bool GFXEngine::Utils::isAbsolutePath(const std::string& filePath)
{
#ifdef _WIN32
	return !filePath.empty() && (filePath[0] == '\\' || filePath[0] == '/' || (filePath.size() > 1 && filePath[1] == ':'));
#else
	return !filePath.empty() && filePath[0] == '/';
#endif
}

void GFXEngine::Utils::log(const std::string& service, const std::string& message)
{
	std::cout << "[" << service << "] " << message << std::endl;
}

void GFXEngine::Utils::saveJsonToFile(const nlohmann::json& jsonData, const std::string& filename)
{
	// Save the JSON data to a file
	std::ofstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file for writing: " + filename);
	}
	file << jsonData.dump(4);
	file.close();
}

nlohmann::json GFXEngine::Utils::loadJsonFromFile(const std::string& filename)
{
	// Load the JSON data from a file
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file for reading: " + filename);
	}
	nlohmann::json jsonData;
	file >> jsonData;
	file.close();
	return jsonData;
}

nlohmann::json GFXEngine::Utils::serializeMat4(const glm::mat4& matrix)
{
	nlohmann::json jsonData;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			jsonData[i][j] = matrix[i][j];
		}
	}
	return jsonData;
}

nlohmann::json GFXEngine::Utils::serializeVec2(const glm::vec2& vector)
{
	nlohmann::json jsonData;
	jsonData[0] = vector.x;
	jsonData[1] = vector.y;
	return jsonData;
}

nlohmann::json GFXEngine::Utils::serializeVec3(const glm::vec3& vector)
{
	nlohmann::json jsonData;
	jsonData[0] = vector.x;
	jsonData[1] = vector.y;
	jsonData[2] = vector.z;
	return jsonData;
}

nlohmann::json GFXEngine::Utils::serializeVec4(const glm::vec4& vector)
{
	nlohmann::json jsonData;
	jsonData[0] = vector.x;
	jsonData[1] = vector.y;
	jsonData[2] = vector.z;
	jsonData[3] = vector.w;
	return jsonData;
}

nlohmann::json GFXEngine::Utils::serializeQuat(const glm::quat& quat)
{
	nlohmann::json jsonData;
	jsonData[0] = quat.x;
	jsonData[1] = quat.y;
	jsonData[2] = quat.z;	
	jsonData[3] = quat.w;
	return jsonData;
}

glm::mat4 GFXEngine::Utils::deserializeMat4(const nlohmann::json& jsonData)
{
	glm::mat4 matrix;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrix[i][j] = jsonData[i][j].get<float>();
		}
	}
	return matrix;
}

glm::vec2 GFXEngine::Utils::deserializeVec2(const nlohmann::json& jsonData)
{
	glm::vec2 vector;
	vector.x = jsonData[0].get<float>();
	vector.y = jsonData[1].get<float>();
	return vector;
}

glm::vec3 GFXEngine::Utils::deserializeVec3(const nlohmann::json& jsonData)
{
	glm::vec3 vector;
	vector.x = jsonData[0].get<float>();
	vector.y = jsonData[1].get<float>();
	vector.z = jsonData[2].get<float>();
	return vector;
}

glm::vec4 GFXEngine::Utils::deserializeVec4(const nlohmann::json& jsonData)
{
	glm::vec4 vector;
	vector.x = jsonData[0].get<float>();
	vector.y = jsonData[1].get<float>();
	vector.z = jsonData[2].get<float>();
	vector.w = jsonData[3].get<float>();
	return vector;
}

glm::quat GFXEngine::Utils::deserializeQuat(const nlohmann::json& jsonData)
{
	glm::quat quat;
	quat.x = jsonData[0].get<float>();
	quat.y = jsonData[1].get<float>();
	quat.z = jsonData[2].get<float>();
	quat.w = jsonData[3].get<float>();
	return quat;
}