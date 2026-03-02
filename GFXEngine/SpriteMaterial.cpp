#include "SpriteMaterial.h"
#include "Utils.h"

void GFXEngine::Graphics::SpriteMaterial::init(Renderer& renderer)
{
	LibGFX::ImageData image = GFXEngine::Utils::loadImage(m_texturePath);
	m_texture = renderer.loadTexture(image);
	m_textureDescriptorSet = renderer.allocateTextureDescriptorSet(m_texture, 0, renderer.getSamplerLayout());
}

void GFXEngine::Graphics::SpriteMaterial::bind(Renderer& renderer, const Camera& camera, uint32_t imageIndex) const
{
	auto cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
	renderer.bindDescriptorSet(cameraDescriptorSet, m_pipeline.getPipelineLayout(), CAMERA_UBO_BINDING, imageIndex);
	renderer.bindDescriptorSet(m_textureDescriptorSet, m_pipeline.getPipelineLayout(), MATERIAL_UBO_BINDING, imageIndex);
}

void GFXEngine::Graphics::SpriteMaterial::destroy(Renderer& renderer)
{
	renderer.disposeTexture(m_texture);
}