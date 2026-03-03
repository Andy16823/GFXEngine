#include "InstancedRenderBehavior.h"
#include "Entity.h"
#include "Renderer.h"
#include <stdexcept>
#include <iostream>

void GFXEngine::Core::InstancedRenderBehavior::init(Graphics::Renderer& renderer)
{
	// Create the ssbo for instance data
	auto bufferSize = m_instanceCount * sizeof(EngineTypes::InstanceData);
	m_instanceDataBuffer = renderer.createBuffer(
		bufferSize,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	);

	// Allocate descriptor set for instance data buffer
	m_instanceDataDescriptorSet = renderer.allocateStorageBufferDescriptorSet(m_instanceDataBuffer, 0, renderer.getStorageBufferLayout());

	// Bake initial instance data
	auto instanceData = bakeInstanceData();

	// Persistently map the buffer for easy updates
	m_mappedInstanceData = renderer.mapBuffer(m_instanceDataBuffer);
	renderer.updateMappedBuffer(m_mappedInstanceData, bufferSize, instanceData.data(), m_instanceCount);
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
	renderer.unmapBuffer(m_instanceDataBuffer);
	renderer.destroyBuffer(m_instanceDataBuffer);
}

void GFXEngine::Core::InstancedRenderBehavior::updateInstance(Graphics::Renderer& renderer, const EngineTypes::InstanceData& instanceData, size_t index)
{
	if (index >= m_instanceCount) {
		throw std::out_of_range("Instance index out of range");
	}
	//auto size = sizeof(EngineTypes::InstanceData);
	//auto offset = index * size;
	//renderer.updateBufferRange(m_instanceDataBuffer, &instanceData, offset);
	renderer.updateMappedBufferRange(m_mappedInstanceData, m_instanceDataBuffer.size, &instanceData, 1, index);
}

std::vector<GFXEngine::EngineTypes::InstanceData> GFXEngine::Core::InstancedRenderBehavior::bakeInstanceData() const
{
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 model = translation * rotation * scale;

	std::vector<EngineTypes::InstanceData> instanceData(m_instanceCount);
	for (size_t i = 0; i < m_instanceCount; ++i) {
		instanceData[i].model = model;
		instanceData[i].extras = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	}
	return instanceData;
}
