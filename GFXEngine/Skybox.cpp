#include "Skybox.h"
#include "Shapes.h"
#include "DataTypes.h"

using namespace GFXEngine::Core;
using namespace GFXEngine::Graphics;

void GFXEngine::Core::Skybox::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	auto [vertices, indices] = Graphics::Shapes::createSkybox();
	
	VkDeviceSize vertexBufferSize = vertices.size() * sizeof(EngineTypes::PositionVertex);
	m_vertexBuffer = renderer.createBuffer(vertexBufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.updateBuffer(m_vertexBuffer, vertices.data(), vertices.size(), true);

	VkDeviceSize indexBufferSize = indices.size() * sizeof(uint32_t);
	m_indexBuffer = renderer.createBuffer(indexBufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.updateBuffer(m_indexBuffer, indices.data(), indices.size(), true);

	m_cubemapDescriptorSet = renderer.allocateCubemapDescriptorSet(m_cubemap, 0, renderer.getCubemapSamplerLayout());
}

void GFXEngine::Core::Skybox::render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (this->isVisible()) {
		Entity::render(scene, renderer, camera, imageIndex);

		VkDescriptorSet cameraDescriptorSet = camera.getDescriptorSet(imageIndex);

		renderer.usePipeline(m_pipeline, imageIndex);
		renderer.bindDescriptorSet(cameraDescriptorSet, m_pipeline.getPipelineLayout(), 0, imageIndex);
		renderer.bindDescriptorSet(m_cubemapDescriptorSet, m_pipeline.getPipelineLayout(), 1, imageIndex);

		renderer.drawBuffers(m_vertexBuffer, m_indexBuffer, 36, imageIndex);
	}
}

void GFXEngine::Core::Skybox::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	renderer.destroyBuffer(m_vertexBuffer);
	renderer.destroyBuffer(m_indexBuffer);
}

size_t GFXEngine::Core::Skybox::getMeshCount() const
{
	return 1;
}

std::pair<const GFXEngine::Graphics::Mesh&, const GFXEngine::Graphics::Material&> GFXEngine::Core::Skybox::getMeshAndMaterial(size_t index) const
{
	throw std::logic_error("The method or operation is not implemented.");
}
