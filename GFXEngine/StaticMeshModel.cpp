#include "StaticMeshModel.h"
#include "Utils.h"

void GFXEngine::Graphics::StaticMeshModel::loadFromFile(const std::string& filePath)
{
	m_meshes = GFXEngine::Utils::loadMeshesFromFile(filePath);
	m_materials = GFXEngine::Utils::loadMaterialsFromFile(filePath);
}

void GFXEngine::Graphics::StaticMeshModel::init(Renderer& renderer)
{
	for (auto& material : m_materials) {
		material.init(renderer);
	}
	for (auto& mesh : m_meshes) {
		mesh.init(renderer);
	}
}

void GFXEngine::Graphics::StaticMeshModel::draw(Renderer& renderer, uint32_t imageIndex, VkPipelineLayout pipelineLayout, std::function<void(Renderer& renderer, VkPipelineLayout pipelineLayout, uint32_t imageIndex, uint32_t meshIndex)> callback) const
{
	for (size_t i = 0; i < m_meshes.size(); i++) {
		const auto& material = m_materials[i % m_materials.size()];
		material.bind(renderer, pipelineLayout, imageIndex, 1);
		if (callback) {
			callback(renderer, pipelineLayout, imageIndex, static_cast<uint32_t>(i));
		}
		m_meshes[i].draw(renderer, imageIndex);
	}
}

void GFXEngine::Graphics::StaticMeshModel::destroy(Renderer& renderer)
{
	for (auto& material : m_materials) {
		material.destroy(renderer);
	}
	for (auto& mesh : m_meshes) {
		mesh.destroy(renderer);
	}
}
