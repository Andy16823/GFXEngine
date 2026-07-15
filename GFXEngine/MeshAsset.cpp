#include "MeshAsset.h"

void GFXEngine::Graphics::MeshAsset::init(Graphics::Renderer& renderer)
{
	if (!m_initialized) {
		if (m_mesh) {
			m_mesh->init(renderer);
			m_initialized = true;
		}
	}
}

void GFXEngine::Graphics::MeshAsset::destroy(Graphics::Renderer & renderer)
{
	if (m_initialized) {
		if (m_mesh) {
			m_mesh->destroy(renderer);
			m_initialized = false;
		}
	}
}
