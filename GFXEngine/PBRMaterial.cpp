#include "PBRMaterial.h"
#include "Utils.h"

void GFXEngine::Graphics::PBRMaterial::init(Renderer& renderer)
{
	auto albedoData = Utils::loadImage(m_albedoPath);
	auto normalData = Utils::loadImage(m_normalPath);
	auto metallicRoughnessData = Utils::loadImage(m_metallicRoughnessPath);
	auto aoData = Utils::loadImage(m_aoPath);

	m_albedo = renderer.loadTexture(albedoData);
	m_normal = renderer.loadTexture(normalData);
	m_metallicRoughness = renderer.loadTexture(metallicRoughnessData);
	m_ao = renderer.loadTexture(aoData);

	m_descriptorSet = renderer.allocatePBRMaterialDescriptorSet(m_albedo, m_normal, m_metallicRoughness, m_ao, 0, renderer.getPBRMaterialLayout());
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
