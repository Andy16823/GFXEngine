#include "DebugBhv.h"
#include "DataTypes.h"
#include "EngineDefinitions.h"
#include "Shapes.h"
#include "Entity.h"
#include "GraphicsPipeline.h"
#include "RenderTask.h"
#include "GraphicResources.h"


using namespace GFXEngine::Core;
using namespace GFXEngine::Graphics;


void GFXEngine::Core::DebugBhv::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	auto entity = this->getEntity();
	auto [vertices, indices] = GFXEngine::Graphics::Shapes::createAabbVertices(entity->getAABB());
	m_debugMesh = std::make_unique<PositionMesh>();
	m_debugMesh->setVertices(std::move(vertices));
	m_debugMesh->setIndices(std::move(indices));
	m_debugMesh->init(renderer);

	// Store index count for rendering
	m_indexCount = static_cast<uint32_t>(indices.size());
}

void GFXEngine::Core::DebugBhv::update(Scene& scene, GFXEngine::Graphics::Camera& camera, float deltaTime)
{

}

void GFXEngine::Core::DebugBhv::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	m_debugMesh->destroy(renderer);
}

void DebugBhv::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	if (!m_isEnabled)
		return;

	// TODO: Rework this to have an mesh
	auto pipeline = context.renderer.getPipeline<GraphicsPipeline>(Defintions::DEBUG_PIPELINE);

	GraphicResources resources;
	resources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
	this->getEntity()->getScene()->getGraphicResources(resources, context.imageIndex);
	this->getEntity()->getGraphicResources(resources, context.imageIndex);

	RenderTaskBuilder taskBuilder;
	taskBuilder.setPipeline(pipeline)
		.setMesh(m_debugMesh.get())
		.setModelMatrix(this->getEntity()->getModelMatrix());
	pipeline->getGraphicsPass().bindResources(taskBuilder, resources);
	renderQueue.addRenderTask(taskBuilder.build());
}

std::vector<GFXEngine::Core::PropertyInfo> DebugBhv::getProperties()
{
	std::vector<PropertyInfo> properties;
	properties.push_back({ 
		.name = "Enabled",
		.data = &m_isEnabled,
	});
	return properties;
}

nlohmann::json DebugBhv::serialize() const
{
	nlohmann::json data = Behavior::serialize();
	data["enabled"] = m_isEnabled;
	return data;
}

void DebugBhv::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags)
{
	Behavior::deserialize(data, context, flags);
	m_isEnabled = data.value("enabled", true);
}