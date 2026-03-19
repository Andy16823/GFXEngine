#include "InstancedModel.h"
#include "Scene3D.h"
#include "EngineDefinitions.h"


void GFXEngine::Core::InstancedModel::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	if (dynamic_cast<Scene3D*>(&scene) == nullptr) {
		throw std::runtime_error("InstancedModel can only be initialized in a Scene3D");
	}

	// Call base entity initialization to initialize behaviors
	Entity::init(scene, renderer);

	// Create storage buffer for instance data
	auto bufferSize = m_instanceCount * sizeof(EngineTypes::InstanceData);
	m_instanceDataBuffer = renderer.createBuffer(
		bufferSize,
		VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	);

	// Allocate descriptor set for instance data buffer
	m_instanceDataDescriptorSet = renderer.allocateStorageBufferDescriptorSet(m_instanceDataBuffer, 0, renderer.getStorageBufferLayout());

	// Bake initial instance data
	m_instanceDataCache = bakeInstanceData();

	// Persistently map the buffer for easy updates
	m_mappedInstanceData = renderer.mapBuffer(m_instanceDataBuffer);
	renderer.updateMappedBuffer(m_mappedInstanceData, bufferSize, m_instanceDataCache.data(), m_instanceCount);
}

void GFXEngine::Core::InstancedModel::render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (this->isVisible()) {
		Entity::render(scene, renderer, camera, imageIndex);

		auto& scene3D = static_cast<Scene3D&>(scene);

		auto meshCount = this->getMeshCount();
		auto cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
		auto pipeline = renderer.getPipeline<Graphics::InstancedGeometryPipeline>(Defintions::INSTANCED_GEOMETRY_PIPELINE);

		renderer.usePipeline(*pipeline, imageIndex);
		renderer.bindDescriptorSet(cameraDescriptorSet, pipeline->getPipelineLayout(), CAMERA_UBO_BINDING, imageIndex);
		scene3D.directionalLight.bind(renderer, camera, *pipeline, LIGHTS_UBO_BINDING, imageIndex);
		renderer.bindDescriptorSet(m_instanceDataDescriptorSet, pipeline->getPipelineLayout(), INSTANCE_SSBO_BINDING, imageIndex);

		for (size_t i = 0; i < meshCount; ++i) {
			auto [mesh, material] = this->getMeshAndMaterial(i);
			material.bind(renderer, camera, *pipeline, imageIndex);
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

GFXEngine::Math::AABB GFXEngine::Core::InstancedModel::computeInstanceAABB(size_t instanceIndex) const
{
	
}

std::vector<GFXEngine::EngineTypes::InstanceData> GFXEngine::Core::InstancedModel::bakeInstanceData() const
{
	std::vector<EngineTypes::InstanceData> instanceData(m_instanceCount);
	for (size_t i = 0; i < m_instanceCount; ++i) {
		instanceData[i].model = this->transform.getModelMatrix();
		instanceData[i].extras = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f); // You can use this for additional per-instance data if needed
	}
	return instanceData;
}

void GFXEngine::Core::InstancedModel::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	Entity::destroy(scene, renderer);
	renderer.unmapBuffer(m_instanceDataBuffer);
	renderer.destroyBuffer(m_instanceDataBuffer);
}

void GFXEngine::Core::InstancedModel::updateInstance(Graphics::Renderer& renderer, const EngineTypes::InstanceData& instanceData, size_t index)
{
	if (index >= m_instanceCount) {
		throw std::out_of_range("Instance index out of range");
	}
	renderer.updateMappedBufferRange(m_mappedInstanceData, m_instanceDataBuffer.size, &instanceData, 1, index);
}

void GFXEngine::Core::InstancedModel::updateInstanceRange(Graphics::Renderer& renderer, const std::span<const EngineTypes::InstanceData>& instanceData, size_t startIndex)
{
	size_t total = startIndex + instanceData.size();
	if (total > m_instanceCount) {
		throw std::out_of_range("Instance range out of range");
	}
	renderer.updateMappedBufferRange(m_mappedInstanceData, m_instanceDataBuffer.size, instanceData.data(), instanceData.size(), startIndex);
}