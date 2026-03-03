#include "InstancedRenderBehavior.h"
#include "Entity.h"
#include "Renderer.h"
#include <stdexcept>
#include <iostream>

void GFXEngine::Core::InstancedRenderBehavior::init(Graphics::Renderer& renderer)
{
	std::cout << "Initializing InstancedRenderBehavior with " << m_instanceCount << " instances." << std::endl;
	auto bufferSize = m_instanceCount * sizeof(EngineTypes::InstanceData);
	m_instanceDataBuffer = renderer.createBuffer(
		bufferSize,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	);
	auto instanceData = bakeInstanceData();
	renderer.updateBuffer(m_instanceDataBuffer, instanceData.data(), m_instanceCount);

	m_instanceDataDescriptorSet = renderer.allocateStorageBufferDescriptorSet(m_instanceDataBuffer, 0, renderer.getStorageBufferLayout());
}

void GFXEngine::Core::InstancedRenderBehavior::update(float deltaTime)
{

}

void GFXEngine::Core::InstancedRenderBehavior::render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	auto entity = this->getEntity();
	auto meshCount = entity->getMeshCount();

	auto cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
	renderer.usePipeline(m_pipeline, imageIndex);
	renderer.bindDescriptorSet(cameraDescriptorSet, m_pipeline.getPipelineLayout(), 0, imageIndex);
	renderer.bindDescriptorSet(m_instanceDataDescriptorSet, m_pipeline.getPipelineLayout(), 2, imageIndex);

	for (size_t i = 0; i < meshCount; ++i) {
		auto [mesh, material] = entity->getMeshAndMaterial(i);
		material.bind(renderer, camera, m_pipeline, imageIndex);
		renderer.drawBuffers(mesh.getVertexBuffer(), mesh.getIndexBuffer(), mesh.getIndexCount(), imageIndex, static_cast<uint32_t>(m_instanceCount));
	}
}

void GFXEngine::Core::InstancedRenderBehavior::destroy(Graphics::Renderer& renderer)
{
	renderer.destroyBuffer(m_instanceDataBuffer);
}

void GFXEngine::Core::InstancedRenderBehavior::updateInstanceData(Graphics::Renderer& renderer, const EngineTypes::InstanceData& instanceData, size_t index)
{
	if (index >= m_instanceCount) {
		throw std::out_of_range("Instance index out of range");
	}
	auto size = sizeof(EngineTypes::InstanceData);
	auto offset = index * size;
	renderer.updateBuffer(m_instanceDataBuffer, instanceData, offset);
}

std::vector<GFXEngine::EngineTypes::InstanceData> GFXEngine::Core::InstancedRenderBehavior::bakeInstanceData() const
{
	std::vector<EngineTypes::InstanceData> instanceData(m_instanceCount);
	for (size_t i = 0; i < m_instanceCount; ++i) {
		instanceData[i].model = glm::mat4(2.0f);
		instanceData[i].extras = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	}
	return instanceData;
}
