#include "EnviromentMap.h"
#include "Shapes.h"
#include "DataTypes.h"
#include "EngineDefinitions.h"
#include "EnviromentPipeline.h"

using namespace GFXEngine::Graphics;

void EnviromentMap::init(GFXEngine::Graphics::Renderer& renderer)
{
	auto [vertices, indices] = Graphics::Shapes::createSkybox();
	
	VkDeviceSize vertexBufferSize = vertices.size() * sizeof(EngineTypes::PositionVertex);
	m_vertexBuffer = renderer.createBuffer(
		vertexBufferSize, 
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.updateBuffer(m_vertexBuffer, vertices.data(), vertices.size(), false);

	VkDeviceSize indexBufferSize = indices.size() * sizeof(uint32_t);
	m_indexBuffer = renderer.createBuffer(
		indexBufferSize, 
		VK_BUFFER_USAGE_INDEX_BUFFER_BIT, 
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.updateBuffer(m_indexBuffer, indices.data(), indices.size(), false);

	m_cubemapDescriptorSet = renderer.allocateCubemapDescriptorSet(m_cubemap, 0);
}

void EnviromentMap::render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	VkDescriptorSet cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
	auto pipeline = renderer.getPipeline<EnviromentPipeline>(Defintions::ENVIRONMENT_PIPELINE);

	renderer.usePipeline(*pipeline, imageIndex);
	renderer.bindDescriptorSet(cameraDescriptorSet, pipeline->getPipelineLayout(), 0, imageIndex);
	renderer.bindDescriptorSet(m_cubemapDescriptorSet, pipeline->getPipelineLayout(), 1, imageIndex);
	renderer.drawBuffers(m_vertexBuffer, m_indexBuffer, 36, imageIndex);
}

void EnviromentMap::destroy(GFXEngine::Graphics::Renderer& renderer)
{
	renderer.destroyBuffer(m_vertexBuffer);
	renderer.destroyBuffer(m_indexBuffer);
}