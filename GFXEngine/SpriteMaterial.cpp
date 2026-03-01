#include "SpriteMaterial.h"
#include "Utils.h"

void GFXEngine::Graphics::SpriteMaterial::init(Renderer& renderer)
{
	LibGFX::ImageData image = GFXEngine::Utils::loadImage(m_texturePath);
	m_texture = renderer.loadTexture(image);
	m_textureDescriptorSet = renderer.allocateTextureDescriptorSet(m_texture, 0, renderer.getSamplerLayout());
}

void GFXEngine::Graphics::SpriteMaterial::bind(Renderer& renderer, uint32_t imageIndex, uint32_t firstSet) const
{
	renderer.bindDescriptorSet(m_textureDescriptorSet, m_pipeline.getPipelineLayout(), firstSet, imageIndex);
}

void GFXEngine::Graphics::SpriteMaterial::destroy(Renderer& renderer)
{
	renderer.disposeTexture(m_texture);
}