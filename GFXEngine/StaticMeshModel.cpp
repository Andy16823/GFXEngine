#include "StaticMeshModel.h"
#include "Utils.h"
#include <cassert>

void GFXEngine::Graphics::StaticMeshModel::init(Renderer& renderer)
{
	if (m_loaded)
	{
		// Ensure we don't initialize more than once without destroying first
		if (m_initialized) {
			return;
		}

		// Initialize materials
		for (auto& material : m_materials) {
			material->init(renderer);
		}

		// Initialize meshes
		for (auto& mesh : m_meshes) {
			mesh.init(renderer);
		}
		m_initialized = true;
	}
}

void GFXEngine::Graphics::StaticMeshModel::destroy(Renderer& renderer)
{
	if (m_initialized) 
	{
		// Destroy materials
		for (auto& material : m_materials) {
			material->destroy(renderer);
		}

		// Destroy meshes
		for (auto& mesh : m_meshes) {
			mesh.destroy(renderer);
		}
		m_initialized = false;
	}
}

void GFXEngine::Graphics::StaticMeshModel::load()
{
	assert(!m_loaded && "StaticMeshModel is already loaded");

	m_meshes = GFXEngine::Utils::loadMeshesFromFile(getFilePath());
	auto materials = GFXEngine::Utils::loadPBRMaterialsFromFile(getFilePath());
	for (auto& material : materials) {
		m_materials.push_back(std::make_unique<PBRMaterial>(std::move(material)));
	}

	m_loaded = true;
}

void GFXEngine::Graphics::StaticMeshModel::unload()
{
	assert(!m_initialized && "Cannot unload StaticMeshModel while it is still initialized");
	if (m_loaded)
	{
		m_meshes.clear();
		m_materials.clear();
		m_loaded = false;
	}
}