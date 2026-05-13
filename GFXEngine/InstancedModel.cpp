#include "InstancedModel.h"
#include "Scene3D.h"
#include "EngineDefinitions.h"


GFXEngine::Core::InstancedModel::InstancedModel(Graphics::MeshModel* meshModel, size_t instanceCount)
	: m_meshModel(meshModel)
{
	m_instanceData.resize(instanceCount, { glm::mat4(1.0f), glm::vec4(0.0f) });
}

void GFXEngine::Core::InstancedModel::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	if (dynamic_cast<Scene3D*>(&scene) == nullptr) {
		throw std::runtime_error("InstancedModel can only be initialized in a Scene3D");
	}

	// Call base entity initialization to initialize behaviors
	Entity::init(scene, renderer);

	// Create storage buffer for instance data
	auto bufferSize = m_instanceData.size() * sizeof(EngineTypes::InstanceData);
	m_instanceDataBuffer = renderer.createBuffer(
		bufferSize,
		VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	);

	// Allocate descriptor set for instance data buffer
	m_instanceDataDescriptorSet = renderer.allocateStorageBufferDescriptorSet(m_instanceDataBuffer, 0, renderer.getStorageBufferLayout());

	// Persistently map the buffer for easy updates
	m_mappedInstanceData = renderer.mapBuffer(m_instanceDataBuffer);
	renderer.updateMappedBuffer(m_mappedInstanceData, bufferSize, m_instanceData.data(), m_instanceData.size());
	m_isDirty = false; // Data is now in sync with GPU
}

void GFXEngine::Core::InstancedModel::render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	// Render the instanced model
	if (this->isVisible()) {
		Entity::render(scene, renderer, camera, imageIndex);

		// Update instance data buffer if there are any pending updates
		if (m_isDirty) {
			renderer.updateMappedBuffer(m_mappedInstanceData, m_instanceData.size() * sizeof(EngineTypes::InstanceData), m_instanceData.data(), m_instanceData.size());
			m_isDirty = false;
		}

		// Render the instanced model using the appropriate pipeline and descriptor sets
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
			renderer.drawBuffers(mesh.getVertexBuffer(), mesh.getIndexBuffer(), mesh.getIndexCount(), imageIndex, static_cast<uint32_t>(m_instanceData.size()));
		}
	}
}

size_t GFXEngine::Core::InstancedModel::getMeshCount() const
{
	return m_meshModel->getMeshCount();
}

std::pair<const GFXEngine::Graphics::Mesh&, const GFXEngine::Graphics::Material&> GFXEngine::Core::InstancedModel::getMeshAndMaterial(size_t index) const
{
	if (index >= m_meshModel->getMeshCount()) {
		throw std::out_of_range("Mesh index out of range");
	}
	return { m_meshModel->getMesh(index), m_meshModel->getMeshMaterial(index) };
}

GFXEngine::Math::AABB GFXEngine::Core::InstancedModel::computeInstanceAABB(size_t instanceIndex) const
{
	if (instanceIndex >= m_instanceData.size()) {
		throw std::out_of_range("Instance index out of range");
	}
	auto instance = m_instanceData[instanceIndex];
	auto aabb = this->getAABB().applyTransform(instance.model);
	return aabb;
}

bool GFXEngine::Core::InstancedModel::isInstanceVisible(size_t instanceIndex) const
{
	if (instanceIndex >= m_instanceData.size()) {
		throw std::out_of_range("Instance index out of range");
	}
	auto instance = m_instanceData[instanceIndex];
	return (instance.extras.x > 0.0f);
}

void GFXEngine::Core::InstancedModel::hideInstance(size_t instanceIndex)
{
	if (instanceIndex >= m_instanceData.size()) {
		throw std::out_of_range("Instance index out of range");
	}
	m_instanceData[instanceIndex].extras.x = 0.0f;
	m_isDirty = true;
}

void GFXEngine::Core::InstancedModel::showInstance(size_t instanceIndex)
{
	if (instanceIndex >= m_instanceData.size()) {
		throw std::out_of_range("Instance index out of range");
	}
	m_instanceData[instanceIndex].extras.x = 1.0f;
	m_isDirty = true;
}

void GFXEngine::Core::InstancedModel::setInstanceModelMatrix(size_t instanceIndex, const glm::mat4& modelMatrix)
{
	if (instanceIndex >= m_instanceData.size()) {
		throw std::out_of_range("Instance index out of range");
	}
	m_instanceData[instanceIndex].model = modelMatrix;
	m_isDirty = true;
}

size_t GFXEngine::Core::InstancedModel::findNextFreeInstance() const
{
	for (size_t i = 0; i < m_instanceData.size(); ++i) {
		if (m_instanceData[i].extras.x <= 0.0f) {
			return i;
		}
	}
	return static_cast<size_t>(-1);
}

glm::mat4 GFXEngine::Core::InstancedModel::getInstanceModelMatrix(size_t instanceIndex) const
{
	if(instanceIndex >= m_instanceData.size()) {
		throw std::out_of_range("Instance index out of range");
	}
	return m_instanceData[instanceIndex].model;
}

void GFXEngine::Core::InstancedModel::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	Entity::destroy(scene, renderer);
	renderer.unmapBuffer(m_instanceDataBuffer);
	renderer.destroyBuffer(m_instanceDataBuffer);
}

void GFXEngine::Core::InstancedModel::updateInstance(const EngineTypes::InstanceData& instanceData, size_t index)
{
	if (index >= m_instanceData.size()) {
		throw std::out_of_range("Instance index out of range");
	}
	m_instanceData[index] = instanceData;
	m_isDirty = true;
}

void GFXEngine::Core::InstancedModel::updateInstanceRange(const std::span<const EngineTypes::InstanceData>& instanceData, size_t startIndex)
{
	size_t total = startIndex + instanceData.size();
	if (total > m_instanceData.size()) {
		throw std::out_of_range("Instance range out of range");
	}
	for (size_t i = 0; i < instanceData.size(); ++i) {
		m_instanceData[startIndex + i] = instanceData[i];
	}
	m_isDirty = true;
}