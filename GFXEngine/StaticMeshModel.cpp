#include "StaticMeshModel.h"
#include "Utils.h"

void GFXEngine::Graphics::StaticMeshModel::loadFromFile(const std::string& filePath, const GeometryPipeline& pipeline)
{
	m_meshes = GFXEngine::Utils::loadMeshesFromFile(filePath);
	m_materials = GFXEngine::Utils::loadMaterialsFromFile(filePath, pipeline);
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

void GFXEngine::Graphics::StaticMeshModel::draw(Renderer& renderer, uint32_t imageIndex, std::function<void(const MeshModel& meshModel, Renderer& renderer, uint32_t imageIndex, uint32_t meshIndex)> callback) const
{
	// Draw each mesh with its corresponding material
	for (size_t i = 0; i < m_meshes.size(); i++) {
		const auto& material = m_materials[i % m_materials.size()];
		const auto& pipeline = material.getPipeline();

		renderer.usePipeline(pipeline, imageIndex);
		material.bind(renderer, imageIndex, MATERIAL_UBO_BINDING);

		if (callback) {
			callback(*this, renderer, imageIndex, static_cast<uint32_t>(i));
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
