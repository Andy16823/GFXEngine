#include "MeshRenderBehavior.h"
#include "EngineDefinitions.h"
#include "Entity.h"
#include <iostream>

void GFXEngine::Core::MeshRenderBehavior::init(Scene& scene, Graphics::Renderer& renderer)
{}

void GFXEngine::Core::MeshRenderBehavior::update(Scene & scene, Graphics::Camera & camera, float deltaTime)
{}

void GFXEngine::Core::MeshRenderBehavior::destroy(Scene & scene, Graphics::Renderer & renderer)
{}

std::string GFXEngine::Core::MeshRenderBehavior::getName() const
{
	return "MeshRenderBehavior";
}

std::vector<GFXEngine::Core::PropertyInfo> GFXEngine::Core::MeshRenderBehavior::getProperties()
{
    std::vector<GFXEngine::Core::PropertyInfo> props;

	props.push_back({
		.name = "Mesh",
		.data = &m_meshRef,
		.hint = PropertyHint::None,
		.metaData = AssetMetaData{ AssetType::Mesh }
		});

	props.push_back({
		.name = "Material",
		.data = &m_materialRef,
		.hint = PropertyHint::None,
		.metaData = AssetMetaData{ AssetType::Material }
		});

	return props;
}

void GFXEngine::Core::MeshRenderBehavior::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	if (!m_meshRef) {
		std::cerr << "Warning: MeshRenderBehavior has no valid mesh reference. Skipping render task." << std::endl;
		return;
	}

	if (!m_materialRef) {
		std::cerr << "Warning: MeshRenderBehavior has no valid material reference. Skipping render task." << std::endl;
		return;
	}

	auto entity = this->getEntity();
	auto mesh = m_meshRef.get<Graphics::MeshAsset>()->getMesh();
	auto material = m_materialRef.get<Graphics::MaterialAsset>()->getMaterial();

	Graphics::GraphicResources resources;
	resources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
	resources[Defintions::MATERIAL_RESOURCE] = material->getDescriptorSet(context.imageIndex);
	entity->getScene()->getGraphicResources(resources, context.imageIndex);
	entity->getGraphicResources(resources, context.imageIndex);

	Graphics::RenderTaskBuilder taskBuilder;
	taskBuilder.setPipeline(m_pipeline)
		.setMesh(mesh)
		.setModelMatrix(entity->getModelMatrix());

	m_pipeline->getGraphicsPass().bindResources(taskBuilder, resources);
	renderQueue.addRenderTask(taskBuilder.build());
}