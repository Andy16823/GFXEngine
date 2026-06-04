#include "Model.h"
#include "Scene3D.h"
#include "EngineDefinitions.h"
#include "AssetManager.h"
#include "RenderTask.h"

using namespace GFXEngine;
using namespace GFXEngine::Core;
using namespace GFXEngine::Graphics;

GFXEngine::Core::Model::Model(Graphics::MeshModel* meshModel)
{
	m_meshModelRef.set(meshModel);
}

void GFXEngine::Core::Model::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	// Call base entity initialization (if any)
	Entity::init(scene, renderer);

	// Ensure the mesh model reference is valid and initialized
	auto meshModel = m_meshModelRef.get<Graphics::MeshModel>();
	if (!meshModel) {
		throw std::runtime_error("Model initialization error: MeshModel reference is invalid");
	}
	assert(meshModel->isInitialized() && "MeshModel must be initialized before building render tasks");
}

void GFXEngine::Core::Model::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	// Ensure the mesh model reference is valid and initialized before building render tasks
	auto meshModel = m_meshModelRef.get<Graphics::MeshModel>();
	if (!meshModel) {
		throw std::runtime_error("Model initialization error: MeshModel reference is invalid");
	}
	assert(meshModel->isInitialized() && "MeshModel must be initialized before building render tasks");
	
	if (!isVisible())
		return;

	if (context.renderPass == RenderPassIteration::GeometryPass) {

		// Get the Pipeline for the render
		auto pipeline = context.renderer.getPipeline<Graphics::GraphicsPipeline>(Defintions::GEOMETRY_PIPELINE);

		// Build the common graphic resources for the entity (camera, scene-level, entity resources)
		Graphics::GraphicResources resources;
		resources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
		this->getScene()->getGraphicResources(resources, context.imageIndex);
		this->getGraphicResources(resources, context.imageIndex);

		for (size_t i = 0; i < this->getMeshCount(); ++i) {
			auto meshMaterialPair = this->getMeshAndMaterial(i);
			if (!meshMaterialPair.has_value()) {
				std::cerr << "Warning: Mesh " << i << " in Model '" << this->name << "' is missing a valid mesh/material pair. Skipping render task for this mesh." << std::endl;
				continue;
			}
			const auto& [mesh, material] = meshMaterialPair.value();

			// Create render task builder and set common properties
			RenderTaskBuilder taskBuilder;
			taskBuilder.setPipeline(pipeline)
				.setMesh(&mesh)
				.setModelMatrix(this->getModelMatrix());

			// Get mesh-specific graphic resources (like material descriptor set)
			this->getMeshMaterialGraphicResources(resources, context.imageIndex, i);

			// Bind resources to the pipeline (this will throw if required resources are missing)
			pipeline->getGraphicsPass().bindResources(taskBuilder, resources);
			renderQueue.addRenderTask(taskBuilder.build());
		}
	}

	Entity::buildRenderTasks(context, renderQueue);
}

std::vector<GFXEngine::Core::PropertyInfo> GFXEngine::Core::Model::getProperties()
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

nlohmann::json GFXEngine::Core::Model::serialize() const
{
	// Serialize base entity data first
	nlohmann::json data = Entity::serialize();

	// Serialize mesh model reference by storing the name of the referenced mesh model asset
	data["meshModel"] = m_meshModelRef.get<Graphics::MeshModel>()->getName();
	return data;
}

void GFXEngine::Core::Model::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags)
{
	// Deserialize base entity data first
	Entity::deserialize(data, context, flags);

	// Deserialize mesh model reference
	if (!data.contains("meshModel") || !data["meshModel"].is_string()) {
		throw std::runtime_error("Model deserialization error: 'meshModel' field is missing or not a string");
	}
	auto modelName = data["meshModel"].get<std::string>();

	// Look up the mesh model asset by name and set the reference
	auto meshModelAsset = context.assets.get<Graphics::MeshModel>(modelName);
	if (!meshModelAsset) {
		throw std::runtime_error("Model deserialization error: MeshModel asset '" + modelName + "' not found");
	}
	m_meshModelRef.set(meshModelAsset);
}

void Model::getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const
{
	
}

void Model::getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const
{
	assert(meshIndex < getMeshCount() && "Mesh index out of range in getGraphicResources");
	auto meshMaterialPair = getMeshAndMaterial(meshIndex);
	if (meshMaterialPair.has_value()) {
		const auto& material = meshMaterialPair->second;
		resources[Defintions::MATERIAL_RESOURCE] = material.getDescriptorSet(imageIndex);
	}
}

size_t GFXEngine::Core::Model::getMeshCount() const
{
	return m_meshModelRef.get<Graphics::MeshModel>()->getMeshCount();
}

GFXEngine::Core::MeshMaterialPair GFXEngine::Core::Model::getMeshAndMaterial(size_t index) const
{
	auto meshModel = m_meshModelRef.get<Graphics::MeshModel>();
	if (index >= meshModel->getMeshCount()) {
		throw std::out_of_range("Mesh index out of range");
	}
	return std::make_optional(
		std::make_pair(std::ref(meshModel->getMesh(index)), std::ref(meshModel->getMeshMaterial(index)))
	);
}