#include "PBRMaterial.h"
#include "Utils.h"

void GFXEngine::Graphics::PBRMaterial::init(Renderer& renderer)
{
	m_albedo = renderer.loadTexture(m_albedoData);
	m_normal = renderer.loadTexture(m_normalData);	
	m_metallicRoughness = renderer.loadTexture(m_metallicRoughnessData);
	m_ao = renderer.loadTexture(m_aoData);

	m_descriptorSet = renderer.allocatePBRMaterialDescriptorSet(m_albedo, m_normal, m_normal, m_ao, 0);
}

void GFXEngine::Graphics::PBRMaterial::bind(Renderer& renderer, const Camera& camera, const LibGFX::Pipeline& pipeline, uint32_t imageIndex) const
{
	renderer.bindDescriptorSet(m_descriptorSet, pipeline.getPipelineLayout(), 1, imageIndex);
}

void GFXEngine::Graphics::PBRMaterial::destroy(Renderer& renderer)
{
	renderer.disposeTexture(m_albedo);
	renderer.disposeTexture(m_normal);
	renderer.disposeTexture(m_metallicRoughness);
	renderer.disposeTexture(m_ao);
}
