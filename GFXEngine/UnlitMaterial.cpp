#include "UnlitMaterial.h"
#include "Utils.h"
#include <iostream>

void GFXEngine::Graphics::UnlitMaterial::init(Renderer& renderer)
{
	// Load texture image data and create Vulkan texture and descriptor set
	LibGFX::ImageData imageData = GFXEngine::Utils::loadImage(m_texturePath, false);
	m_texture = renderer.loadTexture(imageData);
	m_textureDescriptorSet = renderer.allocateTextureDescriptorSet(m_texture, 0);
}

void GFXEngine::Graphics::UnlitMaterial::contributeToRenderTask(RenderTaskBuilder& builder, const RenderContext& context) const
{
	builder.addDescriptorSet(m_textureDescriptorSet, MATERIAL_UBO_BINDING);
}


void GFXEngine::Graphics::UnlitMaterial::destroy(Renderer& renderer)
{
	// Free the texture descriptor set and destroy the Vulkan texture
	renderer.disposeTexture(m_texture);
}