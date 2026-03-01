#include "UnlitMaterial.h"
#include "Utils.h"
#include <iostream>

void GFXEngine::Graphics::UnlitMaterial::init(Renderer& renderer)
{
	// Load image data and create texture
	LibGFX::ImageData imageData = GFXEngine::Utils::loadImage(m_texturePath, false);
	m_texture = renderer.loadTexture(imageData);

	// Allocate descriptor set for the texture
	m_textureDescriptorSet = renderer.allocateTextureDescriptorSet(m_texture, 0, renderer.getSamplerLayout());
}

void GFXEngine::Graphics::UnlitMaterial::bind(Renderer& renderer, VkPipelineLayout pipelineLayout, uint32_t imageIndex, uint32_t firstSet) const
{
	renderer.bindDescriptorSet(m_textureDescriptorSet, pipelineLayout, firstSet, imageIndex);
}

void GFXEngine::Graphics::UnlitMaterial::destroy(Renderer& renderer)
{
	renderer.disposeTexture(m_texture);
}