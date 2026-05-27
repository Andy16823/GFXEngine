#include "SpriteMaterial.h"
#include "Utils.h"

void GFXEngine::Graphics::SpriteMaterial::init(Renderer& renderer)
{
	// Load texture image data and create Vulkan texture and descriptor set
	LibGFX::ImageData image = GFXEngine::Utils::loadImage(m_texturePath);
	m_texture = renderer.loadTexture(image);
	m_textureDescriptorSet = renderer.allocateTextureDescriptorSet(m_texture, 0);
}

void GFXEngine::Graphics::SpriteMaterial::contributeToRenderTask(RenderTaskBuilder& builder, const RenderContext& context) const
{
	builder.addDescriptorSet(m_textureDescriptorSet, MATERIAL_UBO_BINDING);
}

void GFXEngine::Graphics::SpriteMaterial::destroy(Renderer& renderer)
{
	// Free the texture descriptor set and destroy the Vulkan texture
	renderer.disposeTexture(m_texture);
}