#include "Utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdexcept>
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/pbrmaterial.h"
#include <iostream>

LibGFX::ImageData GFXEngine::Utils::loadImage(const std::string& filePath, bool flipVertically)
{
	stbi_set_flip_vertically_on_load(flipVertically);
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
	imageData.pixels = pixels.data();
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

	LibGFX::CubemapData cubemapData;
	for (size_t i = 0; i < 6; i++) {
		stbi_set_flip_vertically_on_load(flipVertically);
		int texWidth, texHeight, texChannels;
		stbi_uc* pixels = stbi_load(filePaths[i].c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
		if (!pixels) {
			throw std::runtime_error("Failed to load cubemap image: " + filePaths[i]);
		}
		cubemapData.pixels[i] = pixels;
		cubemapData.width = static_cast<uint32_t>(texWidth);
		cubemapData.height = static_cast<uint32_t>(texHeight);
		cubemapData.format = VK_FORMAT_R8G8B8A8_UNORM;
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
