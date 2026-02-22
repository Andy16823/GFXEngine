#include "Utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdexcept>
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include <iostream>

LibGFX::ImageData GFXEngine::Utils::loadImage(const std::string& filePath)
{
	stbi_set_flip_vertically_on_load(true);
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

std::vector<GFXEngine::Graphics::Mesh> GFXEngine::Utils::loadMeshesFromFile(const std::string& filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
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
			
			EngineTypes::Vertex3D vertex{};
			vertex.pos = glm::vec3(aiVertex.x, aiVertex.y, aiVertex.z);
			vertex.normal = glm::vec3(aiNormal.x, aiNormal.y, aiNormal.z);
			vertex.texCoord = glm::vec2(aiTexCoord.x, aiTexCoord.y);
			vertex.color = glm::vec3(1.0f); // Default white color TODO: Load vertex colors if available

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

std::vector<GFXEngine::Graphics::UnlitMaterial> GFXEngine::Utils::loadMaterialsFromFile(const std::string& filePath, const GFXEngine::Graphics::GeometryPipeline& pipeline)
{
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
			materials.emplace_back(texturePath.C_Str(), pipeline);
		} else {
			std::cerr << "Warning: Material " << i << " does not have a diffuse texture. Skipping." << std::endl;
		}
	}
	return materials;
}