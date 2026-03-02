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

void GFXEngine::Graphics::UnlitMaterial::bind(Renderer& renderer, const Camera& camera, uint32_t imageIndex) const
{
	auto cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
	renderer.bindDescriptorSet(cameraDescriptorSet, m_pipeline.getPipelineLayout(), CAMERA_UBO_BINDING, imageIndex);
	renderer.bindDescriptorSet(m_textureDescriptorSet, m_pipeline.getPipelineLayout(), MATERIAL_UBO_BINDING, imageIndex);
}

void GFXEngine::Graphics::UnlitMaterial::destroy(Renderer& renderer)
{
	renderer.disposeTexture(m_texture);
}