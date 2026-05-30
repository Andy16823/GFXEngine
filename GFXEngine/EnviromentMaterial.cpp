#include "EnviromentMaterial.h"
#include "Utils.h"

void GFXEngine::Graphics::EnviromentMaterial::init(Renderer& renderer)
{
	m_cubemap = renderer.loadCubemap(m_cubemapData);
	m_cubemapDescriptorSet = renderer.allocateCubemapDescriptorSet(m_cubemap, 0);
}

void GFXEngine::Graphics::EnviromentMaterial::destroy(Renderer& renderer)
{
	renderer.disposeCubemap(m_cubemap);
}