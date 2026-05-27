#include "InstancedModel.h"
#include "Scene3D.h"
#include "EngineDefinitions.h"
#include <stdexcept>
#include <iostream>
#include "Utils.h"
#include "AssetManager.h"


GFXEngine::Core::InstancedModel::InstancedModel(Graphics::MeshModel* meshModel, size_t instanceCount)
{
	m_meshModelRef.set(meshModel);
	m_instanceData.resize(instanceCount, { glm::mat4(1.0f), glm::vec4(0.0f) });
}

void GFXEngine::Core::InstancedModel::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	// Ensure we are in a 3D scene
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
			std::cout << "Updated instance data buffer with " << m_instanceData.size() << " instances." << std::endl;
			m_isDirty = false;
		}

		// Render the instanced model using the appropriate pipeline and descriptor sets
		auto& scene3D = static_cast<Scene3D&>(scene);

		auto meshCount = this->getMeshCount();
		auto cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
		auto pipeline = renderer.getPipeline<Graphics::GraphicsPipeline>(Defintions::INSTANCED_GEOMETRY_PIPELINE);

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
	return m_meshModelRef.get<Graphics::MeshModel>()->getMeshCount();
}

std::pair<const GFXEngine::Graphics::Mesh&, const GFXEngine::Graphics::Material&> GFXEngine::Core::InstancedModel::getMeshAndMaterial(size_t index) const
{
	auto meshModel = m_meshModelRef.get<Graphics::MeshModel>();
	if (index >= meshModel->getMeshCount()) {
		throw std::out_of_range("Mesh index out of range");
	}
	return { meshModel->getMesh(index), meshModel->getMeshMaterial(index) };
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
	renderer.freeStorageBufferDescriptorSet(m_instanceDataDescriptorSet);
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

std::vector<GFXEngine::Core::PropertyInfo> GFXEngine::Core::InstancedModel::getProperties()
{
	// Get base entity properties first
	std::vector<PropertyInfo> properties = Entity::getProperties();

	// Add mesh model reference property
	properties.push_back({
		.name = "Mesh Model",
		.data = &m_meshModelRef,
		.hint = PropertyHint::Asset
		});

	return properties;
}

nlohmann::json GFXEngine::Core::InstancedModel::serialize() const
{
	// Serialize base entity data first
	auto data = Entity::serialize();

	// Serialize mesh model reference by storing the name of the referenced mesh model asset
	data["meshModel"] = m_meshModelRef.get<Graphics::MeshModel>()->getName();

	// Serialize instance data
	data["instanceCount"] = m_instanceData.size();
	data["instances"] = nlohmann::json::array();
	for (const auto& instance : m_instanceData) {
		nlohmann::json instanceJson;
		instanceJson["model"] = Utils::serializeMat4(instance.model);
		instanceJson["extras"] = Utils::serializeVec4(instance.extras);
		data["instances"].push_back(instanceJson);
	}
	return data;
}

void GFXEngine::Core::InstancedModel::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags)
{
	// Deserialize base entity data first
	Entity::deserialize(data, context, flags);

	// Check for mesh model reference and resolve it using the asset manager
	if (!data.contains("meshModel") || !data["meshModel"].is_string()) {
		throw std::runtime_error("InstancedModel deserialization error: 'meshModel' field is missing or not a string");
	}
	auto meshModelAsset = context.assets.get<Graphics::MeshModel>(data["meshModel"].get<std::string>());

	// Ensure the mesh model asset was found and is of the correct type, then set the reference
	if (!meshModelAsset) {
		throw std::runtime_error("InstancedModel deserialization error: Failed to find mesh model asset with name: " + data["meshModel"].get<std::string>());
	}
	m_meshModelRef.set(meshModelAsset);

	// Deserialize instance data
	size_t instanceCount = data.value("instanceCount", 0);
	m_instanceData.resize(instanceCount);
	if (data.contains("instances") && data["instances"].is_array()) {
		for (size_t i = 0; i < data["instances"].size(); ++i) {
			const auto& instanceJson = data["instances"][i];
			if(instanceJson.contains("model") && instanceJson.contains("extras")) {
				m_instanceData[i].model = Utils::deserializeMat4(instanceJson["model"]);
				m_instanceData[i].extras = Utils::deserializeVec4(instanceJson["extras"]);
			} else {
				throw std::runtime_error("InstancedModel deserialization error: Instance data is missing 'model' or 'extras' fields");
			}
		}
	}
}
