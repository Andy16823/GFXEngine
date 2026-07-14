#include "MeshRenderBehavior.h"
#include "EngineDefinitions.h"
#include "Entity.h"

void GFXEngine::Core::MeshRenderBehavior::init(Scene& scene, Graphics::Renderer& renderer)
{}

void GFXEngine::Core::MeshRenderBehavior::update(Scene & scene, Graphics::Camera & camera, float deltaTime)
{}

void GFXEngine::Core::MeshRenderBehavior::destroy(Scene & scene, Graphics::Renderer & renderer)
{}

std::string GFXEngine::Core::MeshRenderBehavior::getName() const
{
    return std::string();
}

std::vector<GFXEngine::Core::PropertyInfo> GFXEngine::Core::MeshRenderBehavior::getProperties()
{
    return std::vector<PropertyInfo>();
}

void GFXEngine::Core::MeshRenderBehavior::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	auto entity = this->getEntity();

	Graphics::GraphicResources resources;
	resources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
	resources[Defintions::MATERIAL_RESOURCE] = m_material->getDescriptorSet(context.imageIndex);
	entity->getScene()->getGraphicResources(resources, context.imageIndex);
	entity->getGraphicResources(resources, context.imageIndex);

	Graphics::RenderTaskBuilder taskBuilder;
	taskBuilder.setPipeline(m_pipeline)
		.setMesh(m_mesh)
		.setModelMatrix(entity->getModelMatrix());

	m_pipeline->getGraphicsPass().bindResources(taskBuilder, resources);
	renderQueue.addRenderTask(taskBuilder.build());
}