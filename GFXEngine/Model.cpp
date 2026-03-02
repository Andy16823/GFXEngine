#include "Model.h"

void GFXEngine::Core::Model::render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (isVisible()) {
		Entity::render(renderer, camera, imageIndex);
	}
}

size_t GFXEngine::Core::Model::getMeshCount() const
{
	return m_meshModel.getMeshCount();
}

std::pair<const GFXEngine::Graphics::Mesh&, const GFXEngine::Graphics::Material&> GFXEngine::Core::Model::getMeshAndMaterial(size_t index) const
{
	if (index >= m_meshModel.getMeshCount()) {
		throw std::out_of_range("Mesh index out of range");
	}
	return { m_meshModel.getMesh(index), m_meshModel.getMeshMaterial(index) };
}
