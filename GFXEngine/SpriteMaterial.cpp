#include "SpriteMaterial.h"
#include "Utils.h"

void GFXEngine::Graphics::SpriteMaterial::init(Renderer& renderer)
{
	// Load texture image data and create Vulkan texture and descriptor set
	LibGFX::ImageData image = GFXEngine::Utils::loadImage(m_texturePath);
	m_texture = renderer.loadTexture(image);
	m_textureDescriptorSet = renderer.allocateTextureDescriptorSet(m_texture, 0, renderer.getSamplerLayout());
}

void GFXEngine::Graphics::SpriteMaterial::bind(Renderer& renderer, const Camera& camera, const LibGFX::Pipeline& pipeline, uint32_t imageIndex) const
{
	// Bind the texture descriptor set to the pipeline
	renderer.bindDescriptorSet(m_textureDescriptorSet, pipeline.getPipelineLayout(), 1, imageIndex);
}

void GFXEngine::Graphics::SpriteMaterial::destroy(Renderer& renderer)
{
	// Free the texture descriptor set and destroy the Vulkan texture
	renderer.disposeTexture(m_texture);
}