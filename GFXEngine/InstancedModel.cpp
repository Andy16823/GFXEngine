#include "InstancedModel.h"
#include "Scene3D.h"
#include "EngineDefinitions.h"
#include <stdexcept>
#include <iostream>
#include "Utils.h"
#include "AssetManager.h"
#include "RenderTask.h"
#include "InstanceHandle.h"

using namespace GFXEngine;
using namespace GFXEngine::Core;
using namespace GFXEngine::Graphics;

GFXEngine::Core::InstancedModel::InstancedModel(Graphics::MeshModel* meshModel, size_t instanceCount)
{
	m_meshModelRef.set(meshModel);
	m_instanceData.resize(instanceCount, { glm::mat4(1.0f), glm::vec4(0.0f) });
}

void GFXEngine::Core::InstancedModel::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	// Call base entity initialization to initialize behaviors
	Entity::init(scene, renderer);

	// Ensure the mesh model reference is valid and initialized
	auto meshModel = m_meshModelRef.get<Graphics::MeshModel>();
	if (!meshModel) {
		throw std::runtime_error("InstancedModel initialization error: MeshModel reference is invalid");
	}
	assert(meshModel->isInitialized() && "MeshModel must be initialized before initializing InstancedModel");

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

void GFXEngine::Core::InstancedModel::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	// Ensure the mesh model reference is valid and initialized before building render tasks
	auto meshModel = m_meshModelRef.get<Graphics::MeshModel>();
	if (!meshModel) {
		throw std::runtime_error("InstancedModel render error: MeshModel reference is invalid");
	}
	assert(meshModel->isInitialized() && "MeshModel must be initialized before building render tasks for InstancedModel");

	if (!isVisible())
		return;

	if (m_isDirty) {
		context.renderer.updateMappedBuffer(m_mappedInstanceData, m_instanceData.size() * sizeof(EngineTypes::InstanceData), m_instanceData.data(), m_instanceData.size());
		std::cout << "Updated instance data buffer with " << m_instanceData.size() << " instances." << std::endl;
		m_isDirty = false;
	}

	if (context.renderPass == RenderPassIteration::GeometryPass) {

		// Get pipeline to render with
		auto pipeline = context.renderer.getPipeline<Graphics::GraphicsPipeline>(Defintions::INSTANCED_GEOMETRY_PIPELINE);
		
		// Build render resources (camera, scene-level, entity-level)
		Graphics::GraphicResources resources;
		resources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
		this->getScene()->getGraphicResources(resources, context.imageIndex);
		this->getGraphicResources(resources, context.imageIndex);

		// Create render task for every mesh
		auto meshCount = this->getMeshCount();
		for (size_t i = 0; i < meshCount; ++i) {
			auto meshMaterialPair = this->getMeshAndMaterial(i);
			if (!meshMaterialPair.has_value()) {
				std::cerr << "Warning: Mesh " << i << " in InstancedModel '" << this->name << "' is missing a valid mesh/material pair. Skipping render task for this mesh." << std::endl;
				continue;
			}
			const auto& [mesh, material] = meshMaterialPair.value();

			RenderTaskBuilder taskBuilder;
			taskBuilder.setPipeline(pipeline)
				.setMesh(&mesh)
				.setModelMatrix(this->getModelMatrix())
				.setInstanceCount(static_cast<uint32_t>(m_instanceData.size()));

			// Get mesh-specific graphic resources (like material descriptor set) and bind to the pipeline
			this->getMeshMaterialGraphicResources(resources, context.imageIndex, i);
			pipeline->getGraphicsPass().bindResources(taskBuilder, resources);

			renderQueue.addRenderTask(taskBuilder.build());
		}
	}

	// Create child render tasks
	Entity::buildRenderTasks(context, renderQueue);
}

size_t GFXEngine::Core::InstancedModel::getMeshCount() const
{
	return m_meshModelRef.get<Graphics::MeshModel>()->getMeshCount();
}

GFXEngine::Core::MeshMaterialPair GFXEngine::Core::InstancedModel::getMeshAndMaterial(size_t index) const
{
	auto meshModel = m_meshModelRef.get<Graphics::MeshModel>();
	if (index >= meshModel->getMeshCount()) {
		throw std::out_of_range("Mesh index out of range");
	}
	return std::make_optional(
		std::make_pair(std::ref(meshModel->getMesh(index)), std::ref(meshModel->getMeshMaterial(index)))
	);
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

std::unique_ptr<GFXEngine::Core::InstanceHandle> InstancedModel::instantiate(const std::string& name)
{
	auto freeIndex = findNextFreeInstance();
	if (freeIndex == static_cast<size_t>(-1)) {
		throw std::runtime_error("No free instance slots available in InstancedModel");
	}
	return instantiate(name, freeIndex);
}

std::unique_ptr<GFXEngine::Core::InstanceHandle> InstancedModel::instantiate(const std::string& name, size_t instanceIndex)
{
	return std::make_unique<InstanceHandle>(name, this, instanceIndex);
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

void InstancedModel::getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const
{
	resources[Defintions::INSTANCE_DATA_RESOURCE] = m_instanceDataDescriptorSet;
}

void InstancedModel::getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const
{
	assert(meshIndex < getMeshCount() && "Mesh index out of range in getGraphicResources");
	auto meshMaterialPair = getMeshAndMaterial(meshIndex);
	if (!meshMaterialPair.has_value()) {
		std::cerr << "Warning: Mesh " << meshIndex << " in InstancedModel '" << this->name << "' is missing a valid mesh/material pair. Cannot get graphic resources for this mesh." << std::endl;
		return;
	}
	const auto& material = meshMaterialPair->second;
	resources[Defintions::MATERIAL_RESOURCE] = material.getDescriptorSet(imageIndex);
}