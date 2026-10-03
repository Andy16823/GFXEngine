#include "Model.h"
#include "Scene3D.h"
#include "EngineDefinitions.h"
#include "AssetManager.h"
#include "RenderTask.h"

using namespace GFXEngine;
using namespace GFXEngine::Core;
using namespace GFXEngine::Graphics;

void GFXEngine::Core::Model::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	Entity::init(scene, renderer);

	auto meshModel = m_meshModelRef->as<MeshModel>();
	if (!meshModel) {
		throw std::runtime_error("Model initialization error: MeshModel reference is invalid");
	}
	assert(meshModel->isInitialized() && "MeshModel must be initialized before building render tasks");
}

void GFXEngine::Core::Model::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	// Ensure the mesh model reference is valid and initialized before building render tasks
	auto meshModel = m_meshModelRef->as<MeshModel>();
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
        resources[Defintions::FRAME_RESOURCE] = context.frameContext.getDescriptorSet(context.imageIndex);
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
		.data = &m_meshModelRef.value(),
		.hint = PropertyHint::Asset,
		.metaData = AssetMetaData { AssetType::MeshModel }
		});

	return properties;
}

nlohmann::json GFXEngine::Core::Model::serialize() const
{
	// Serialize base entity data first
	nlohmann::json data = Entity::serialize();

	// Serialize mesh model reference by storing the name of the referenced mesh model asset
	if(m_meshModelRef.has_value()) 
	{
		data["meshModel"] = m_meshModelRef.value()->getName();
	}
	return data;
}

void Model::requireAsset(RequiredAssets& assets)
{
	Entity::requireAsset(assets);
	auto meshModel = m_meshModelRef->as<MeshModel>();
	if (!meshModel) {
		throw std::runtime_error("Model requireAsset error: MeshModel reference is invalid");
	}
	assets.emplace(meshModel->getName());
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
	m_meshModelRef = context.assets.get<Graphics::MeshModel>(modelName);
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
	if (m_meshModelRef.has_value()) {
		auto meshmodel = m_meshModelRef.value()->as<Graphics::MeshModel>();
		return meshmodel->getMeshCount();
	}
	return 0;
}

GFXEngine::Core::MeshMaterialPair GFXEngine::Core::Model::getMeshAndMaterial(size_t index) const
{
	if (!m_meshModelRef.has_value()) {
		throw std::runtime_error("MeshModel reference has no value");
	}

	auto meshModel = m_meshModelRef.value()->as<Graphics::MeshModel>();
	if (!meshModel) {
		throw std::runtime_error("MeshModel is not of type Graphics::MeshModel");
	}

	if (index >= meshModel->getMeshCount()) {
		throw std::out_of_range("Mesh index out of range");
	}

	return std::make_optional(
		std::make_pair(std::ref(meshModel->getMesh(index)), std::ref(meshModel->getMeshMaterial(index)))
	);
}