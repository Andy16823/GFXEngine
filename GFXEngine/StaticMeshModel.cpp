#include "StaticMeshModel.h"
#include "Utils.h"

GFXEngine::Graphics::StaticMeshModel::StaticMeshModel(const std::string& filePath, MaterialType materialType)
{
	this->loadFromFile(filePath, materialType);
}

void GFXEngine::Graphics::StaticMeshModel::init(Renderer& renderer)
{
	// Initialize materials
	for (auto& material : m_materials) {
		material->init(renderer);
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
		material->destroy(renderer);
	}

	// Destroy meshes
	for (auto& mesh : m_meshes) {
		mesh.destroy(renderer);
	}
}

void GFXEngine::Graphics::StaticMeshModel::loadFromFile(const std::string& filePath, MaterialType materialType)
{
	m_meshes = GFXEngine::Utils::loadMeshesFromFile(filePath);
	switch (materialType) {
	case MaterialType::Unlit:
		loadAsUnlit(filePath);
		break;
	case MaterialType::PBR:
		loadAsPBR(filePath);
		break;
	default:
		loadAsPBR(filePath);
	}
}

void GFXEngine::Graphics::StaticMeshModel::loadAsUnlit(const std::string& filePath)
{
	auto materials = GFXEngine::Utils::loadMaterialsFromFile(filePath);
	for (auto& material : materials) {
		m_materials.push_back(std::make_unique<UnlitMaterial>(std::move(material)));
	}
}

void GFXEngine::Graphics::StaticMeshModel::loadAsPBR(const std::string& filePath)
{
	auto materials = GFXEngine::Utils::loadPBRMaterialsFromFile(filePath);
	for (auto& material : materials) {
		m_materials.push_back(std::make_unique<PBRMaterial>(std::move(material)));
	}
}
