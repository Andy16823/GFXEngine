#include "InstancedModel.h"


void GFXEngine::Core::InstancedModel::init(GFXEngine::Graphics::Renderer& renderer)
{
	// Create storage buffer for instance data
	auto bufferSize = m_instanceCount * sizeof(EngineTypes::InstanceData);
	m_instanceDataBuffer = renderer.createBuffer(
		bufferSize,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	);

	// Allocate descriptor set for instance data buffer
	m_instanceDataDescriptorSet = renderer.allocateStorageBufferDescriptorSet(m_instanceDataBuffer, 0, m_pipeline.getInstanceDataDescriptorSetLayout());

	// Bake initial instance data
	auto instanceData = bakeInstanceData();

	// Persistently map the buffer for easy updates
	m_mappedInstanceData = renderer.mapBuffer(m_instanceDataBuffer);
	renderer.updateMappedBuffer(m_mappedInstanceData, bufferSize, instanceData.data(), m_instanceCount);
}

void GFXEngine::Core::InstancedModel::render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (this->isVisible()) {
		Entity::render(renderer, camera, imageIndex);

		auto meshCount = this->getMeshCount();

		auto cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
		renderer.usePipeline(m_pipeline, imageIndex);
		renderer.bindDescriptorSet(cameraDescriptorSet, m_pipeline.getPipelineLayout(), 0, imageIndex);
		renderer.bindDescriptorSet(m_instanceDataDescriptorSet, m_pipeline.getPipelineLayout(), 2, imageIndex);

		for (size_t i = 0; i < meshCount; ++i) {
			auto [mesh, material] = this->getMeshAndMaterial(i);
			material.bind(renderer, camera, m_pipeline, imageIndex);
			renderer.drawBuffers(mesh.getVertexBuffer(), mesh.getIndexBuffer(), mesh.getIndexCount(), imageIndex, static_cast<uint32_t>(m_instanceCount));
		}
	}
}

size_t GFXEngine::Core::InstancedModel::getMeshCount() const
{
	return m_meshModel.getMeshCount();
}

std::pair<const GFXEngine::Graphics::Mesh&, const GFXEngine::Graphics::Material&> GFXEngine::Core::InstancedModel::getMeshAndMaterial(size_t index) const
{
	if (index >= m_meshModel.getMeshCount()) {
		throw std::out_of_range("Mesh index out of range");
	}
	return { m_meshModel.getMesh(index), m_meshModel.getMeshMaterial(index) };
}

std::vector<GFXEngine::EngineTypes::InstanceData> GFXEngine::Core::InstancedModel::bakeInstanceData() const
{
	std::vector<EngineTypes::InstanceData> instanceData(m_instanceCount);
	for (size_t i = 0; i < m_instanceCount; ++i) {
		instanceData[i].model = this->transform.getModelMatrix();
		instanceData[i].extras = glm::vec4(0.0f); // You can use this for additional per-instance data if needed
	}
	return instanceData;
}



void GFXEngine::Core::InstancedModel::destroy(GFXEngine::Graphics::Renderer& renderer)
{
	renderer.unmapBuffer(m_instanceDataBuffer);
	renderer.destroyBuffer(m_instanceDataBuffer);
}

void GFXEngine::Core::InstancedModel::updateInstance(Graphics::Renderer& renderer, const EngineTypes::InstanceData& instanceData, size_t index)
{
	if (index >= m_instanceCount) {
		throw std::out_of_range("Instance index out of range");
	}
	renderer.updateMappedBuffer(m_mappedInstanceData, m_instanceDataBuffer.size, &instanceData, 1);
}

void GFXEngine::Core::InstancedModel::updateInstanceRange(Graphics::Renderer& renderer, const std::span<const EngineTypes::InstanceData>& instanceData, size_t startIndex)
{
	size_t total = startIndex + instanceData.size();
	if (total > m_instanceCount) {
		throw std::out_of_range("Instance range out of range");
	}
	renderer.updateMappedBuffer(m_mappedInstanceData, m_instanceDataBuffer.size, instanceData.data(), instanceData.size());
}