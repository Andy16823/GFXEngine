#include "StaticMeshModel.h"
#include "Utils.h"

GFXEngine::Graphics::StaticMeshModel::StaticMeshModel(const std::string& filePath)
{
	this->loadFromFile(filePath);
}

void GFXEngine::Graphics::StaticMeshModel::init(Renderer& renderer)
{
	// Initialize materials
	for (auto& material : m_materials) {
		material.init(renderer);
	}

	// Initialize meshes
	for (auto& mesh : m_meshes) {
		mesh.init(renderer);
	}
}

void GFXEngine::Graphics::StaticMeshModel::destroy(Renderer& renderer)
{
	// Destroy materials
	for (auto& material : m_materials) {
		material.destroy(renderer);
	}

	// Destroy meshes
	for (auto& mesh : m_meshes) {
		mesh.destroy(renderer);
	}
}

void GFXEngine::Graphics::StaticMeshModel::loadFromFile(const std::string& filePath)
{
	m_meshes = GFXEngine::Utils::loadMeshesFromFile(filePath);
	m_materials = GFXEngine::Utils::loadMaterialsFromFile(filePath);
}
