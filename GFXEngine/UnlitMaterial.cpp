#include "UnlitMaterial.h"
#include "Utils.h"
#include <iostream>

void GFXEngine::Graphics::UnlitMaterial::init(Renderer& renderer)
{
	std::cout << "Initializing UnlitMaterial with texture: " << m_texturePath << std::endl;
	LibGFX::ImageData imageData = GFXEngine::Utils::loadImage(m_texturePath);
	m_texture = renderer.loadTexture(imageData);
	m_textureDescriptorSet = renderer.allocateTextureDescriptorSet(m_texture, 0, m_pipeline.getTextureDescriptorSetLayout());
	std::cout << "UnlitMaterial initialized successfully." << std::endl;
}

void GFXEngine::Graphics::UnlitMaterial::bind(Renderer& renderer, Camera& camera, uint32_t imageIndex) const
{
	renderer.usePipeline(m_pipeline, imageIndex);
	std::vector<VkDescriptorSet> descriptorSets = {
		camera.getDescriptorSet(imageIndex),
		m_textureDescriptorSet
	};
	renderer.bindDescriptorSets(descriptorSets, m_pipeline.getPipelineLayout(), imageIndex);
}

void GFXEngine::Graphics::UnlitMaterial::destroy(Renderer& renderer)
{
	renderer.disposeTexture(m_texture);
}

VkPipelineLayout GFXEngine::Graphics::UnlitMaterial::getPipelineLayout() const
{
	return m_pipeline.getPipelineLayout();
}
