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
	Entity::init(scene, renderer);

	if (dynamic_cast<Scene3D*>(&scene) == nullptr) {
		throw std::runtime_error("Model can only be initialized in a Scene3D");
	}
}

void GFXEngine::Core::Model::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	if (!isVisible())
		return;

	if (context.renderPass == RenderPassIteration::GeometryPass) {

		// Get the Pipeline for the render
		auto pipeline = context.renderer.getPipeline<Graphics::GraphicsPipeline>(Defintions::GEOMETRY_PIPELINE);

		// Build graphic resources for the render task, starting with camera and scene-level resources
		Graphics::GraphicResources resources;
		resources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
		this->getScene()->getGraphicResources(resources, context.imageIndex);

		for (size_t i = 0; i < this->getMeshCount(); ++i) {
			const auto& [mesh, material] = this->getMeshAndMaterial(i);

			// Create render task builder and set common properties
			RenderTaskBuilder taskBuilder;
			taskBuilder.setPipeline(pipeline)
				.setMesh(&mesh)
				.setModelMatrix(this->transform.getModelMatrix());

			// Get entity-specific graphic resources
			this->getGraphicResources(resources, context.imageIndex, i);

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

size_t GFXEngine::Core::Model::getMeshCount() const
{
	return m_meshModelRef.get<Graphics::MeshModel>()->getMeshCount();
}

std::pair<const GFXEngine::Graphics::Mesh&, const GFXEngine::Graphics::Material&> GFXEngine::Core::Model::getMeshAndMaterial(size_t index) const
{
	auto meshModel = m_meshModelRef.get<Graphics::MeshModel>();
	if (index >= meshModel->getMeshCount()) {
		throw std::out_of_range("Mesh index out of range");
	}
	return { meshModel->getMesh(index), meshModel->getMeshMaterial(index) };
}

void Model::getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const
{
	assert(meshIndex < getMeshCount() && "Mesh index out of range in getGraphicResources");
	const auto& material = getMeshAndMaterial(meshIndex).second;
	resources[Defintions::MATERIAL_RESOURCE] = material.getDescriptorSet(imageIndex);
}