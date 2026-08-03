#include "MaterialAsset.h"

void GFXEngine::Graphics::MaterialAsset::init(Graphics::Renderer& renderer)
{
	if (!m_initialized) {
		if (m_material) {
			m_material->init(renderer);
			m_initialized = true;
		}
	}
}

void GFXEngine::Graphics::MaterialAsset::destroy(Graphics::Renderer & renderer)
{
	if (m_initialized) {
		if (m_material) {
			m_material->destroy(renderer);
			m_initialized = false;
		}
	}
}