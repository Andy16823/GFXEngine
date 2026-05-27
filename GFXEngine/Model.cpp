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


//void GFXEngine::Core::Model::render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
//{
//	if (isVisible()) {
//		Entity::render(scene, renderer, camera, imageIndex);
//
//		auto& scene3D = static_cast<Scene3D&>(scene);
//
//		// Get camera descriptor set and model matrix
//		VkDescriptorSet cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
//		glm::mat4 modelMatrix = this->transform.getModelMatrix();
//
//		// TODO: Create an render mode flag to switch between different pipelines (e.g. wireframe, unlit, pbr, etc.)
//		auto pipeline = renderer.getPipeline<Graphics::GraphicsPipeline>(Defintions::GEOMETRY_PIPELINE);
//		renderer.usePipeline(*pipeline, imageIndex);
//		renderer.bindDescriptorSet(cameraDescriptorSet, pipeline->getPipelineLayout(), CAMERA_UBO_BINDING, imageIndex);
//		renderer.bindPushConstants(&modelMatrix, sizeof(glm::mat4), pipeline->getPipelineLayout(), imageIndex);
//		scene3D.directionalLight.bind(renderer, camera, *pipeline, LIGHTS_UBO_BINDING, imageIndex);
//
//		// Render each mesh of the entity
//		for (size_t i = 0; i < this->getMeshCount(); ++i) {
//			auto [mesh, material] = this->getMeshAndMaterial(i);
//			material.bind(renderer, camera, *pipeline, imageIndex);
//			renderer.drawBuffers(mesh.getVertexBuffer(), mesh.getIndexBuffer(), mesh.getIndexCount(), imageIndex);
//		}
//	}
//}

void GFXEngine::Core::Model::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	if (!isVisible())
		return;

	Entity::buildRenderTasks(context, renderQueue);

	if (context.renderPass == RenderPassIteration::GeometryPass) {
		// Get scene as scene3d
		Scene3D* scene3D = this->getScene()->as<Scene3D>();

		// Get Descriptor Sets, model matrix, and pipeline
		VkDescriptorSet cameraDescriptorSet = context.camera.getDescriptorSet(context.imageIndex);
		glm::mat4 modelMatrix = this->transform.getModelMatrix();
		auto pipeline = context.renderer.getPipeline<Graphics::GraphicsPipeline>(Defintions::GEOMETRY_PIPELINE);

		// Build render task for each mesh of the model
		RenderTaskBuilder taskBuilder;
		taskBuilder.setPipeline(pipeline)
			.setModelMatrix(modelMatrix)
			.addDescriptorSet(cameraDescriptorSet, CAMERA_UBO_BINDING)
			.addPushConstant(&modelMatrix, sizeof(glm::mat4));
		scene3D->directionalLight.contributeToRenderTask(taskBuilder, context);

		// For each mesh, set the mesh and material in the render task and add it to the render queue
		for (size_t i = 0; i < this->getMeshCount(); ++i) {
			auto [mesh, material] = this->getMeshAndMaterial(i);
			taskBuilder.setMesh(&mesh);
			material.contributeToRenderTask(taskBuilder, context);
			renderQueue.addRenderTask(taskBuilder.build());
		}
	}
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