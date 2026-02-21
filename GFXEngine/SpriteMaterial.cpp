#include "SpriteMaterial.h"
#include "Utils.h"

void GFXEngine::Graphics::SpriteMaterial::init(Renderer& renderer)
{
	LibGFX::ImageData image = GFXEngine::Utils::loadImage(m_texturePath);
	m_texture = renderer.loadTexture(image);
	m_textureDescriptorSet = renderer.allocateTextureDescriptorSet(m_texture, 0, m_pipeline.getTextureDescriptorSetLayout());
}

void GFXEngine::Graphics::SpriteMaterial::bind(Renderer& renderer, Camera& camera, uint32_t imageIndex)
{
	renderer.usePipeline(m_pipeline, imageIndex);
	std::vector<VkDescriptorSet> descriptorSets = {
		camera.getDescriptorSet(imageIndex),
		m_textureDescriptorSet
	};
	renderer.bindDescriptorSets(descriptorSets, m_pipeline.getPipelineLayout(), imageIndex);
}

void GFXEngine::Graphics::SpriteMaterial::destroy(Renderer& renderer)
{
	renderer.disposeTexture(m_texture);
}
