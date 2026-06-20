#include "Scene3D.h"
#include "AssetManager.h"
#include "EntityFactory.h"
#include "Utils.h"
#include "EngineDefinitions.h"
#include "IGraphicsPass.h"
#include <cassert>

void GFXEngine::Core::Scene3D::renderSerial(GFXEngine::Graphics::RenderContext& context)
{
	for (auto& entity : m_entities) {
		if (entity->isVisible())
		{
			entity->buildRenderTasks(context, m_renderQueue);
		}
	}
}

void GFXEngine::Core::Scene3D::renderParallel(GFXEngine::Graphics::RenderContext& context)
{
	std::vector<GFXEngine::Graphics::RenderQueue> perThreadsQueues(64);

	this->forEachEntityPar([&context, &perThreadsQueues](Entity& entity, int threadIndex) {
		if (entity.isVisible())
		{
			entity.buildRenderTasks(context, perThreadsQueues[threadIndex]);
		}
		});

	for (auto& queue : perThreadsQueues) {
		m_renderQueue.append(std::move(queue));
	}
}

void GFXEngine::Core::Scene3D::renderEnvMap(GFXEngine::Graphics::RenderContext& context, const GFXEngine::Graphics::EnvironmentMap& envMap)
{
	assert(envMap.isInitialized() && "EnvironmentMap must be initialized before rendering");

	auto pipeline = context.renderer.getPipeline<Graphics::GraphicsPipeline>(Defintions::ENVIRONMENT_PIPELINE);
	
	Graphics::GraphicResources resources;
	resources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
	resources[Defintions::MATERIAL_RESOURCE] = envMap.getMaterial().getDescriptorSet(context.imageIndex);
	resources[Defintions::ENVIRONMENT_MAP_RESOURCE] = envMap.getDescriptorSet(context.imageIndex);
	this->getGraphicResources(resources, context.imageIndex);
	
	GFXEngine::Graphics::RenderTaskBuilder builder;
	builder.setPipeline(pipeline)
		.setMesh(&envMap.getMesh())
		.setRenderLayer(Graphics::RenderLayer::Skybox);

	pipeline->getGraphicsPass().bindResources(builder, resources);
	m_renderQueue.addRenderTask(builder.build());
}

void GFXEngine::Core::Scene3D::init(Graphics::Renderer& renderer)
{
	directionalLight.init(renderer);
	fog.init(renderer);
	for (auto& entity : m_entities)
	{
		entity->init(*this, renderer);
	}
}

void GFXEngine::Core::Scene3D::update(Graphics::Camera& camera, float deltaTime)
{
	for (auto& entity : m_entities)
	{
		entity->update(*this, camera, deltaTime);
	}
}

void GFXEngine::Core::Scene3D::beforeRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	directionalLight.update(renderer, camera, imageIndex);
	fog.update(renderer, camera, imageIndex);
}

void GFXEngine::Core::Scene3D::render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	GFXEngine::Graphics::RenderContext context{
		.renderer = renderer,
		.camera = camera,
		.imageIndex = imageIndex,
		.renderPass = Graphics::RenderPassIteration::GeometryPass
	};

	if (m_useParallelRendering) 
	{
		renderParallel(context);
	}
	else 
	{
		renderSerial(context);
	}

	if (const auto* envMap = m_environmentMapRef.get<Graphics::EnvironmentMap>()) 
	{
		this->renderEnvMap(context, *envMap);
	}

	m_renderQueue.sort();
	m_renderQueue.execute(renderer, camera, imageIndex);
}

void GFXEngine::Core::Scene3D::afterRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	// TODO: Add remove entitys here or add enqued entitys
}

void GFXEngine::Core::Scene3D::destroy(Graphics::Renderer& renderer)
{
	directionalLight.destroy(renderer);
	fog.destroy(renderer);
	for (auto& entity : m_entities)
	{
		entity->destroy(*this, renderer);
	}
	m_entities.clear();
}

void GFXEngine::Core::Scene3D::input(int key, int mods, int action)
{

}

std::vector<GFXEngine::Core::PropertyInfo> GFXEngine::Core::Scene3D::getProperties()
{
	std::vector<PropertyInfo> properties;

	properties.push_back({
		.name = "Light Direction",
		.data = &directionalLight.direction,
		});

	properties.push_back({
		.name = "Light Color",
		.data = &directionalLight.color,
		.hint = PropertyHint::Color
		});

	properties.push_back({
		.name = "Light Intensity",
		.data = &directionalLight.intensity,
		});

	properties.push_back({
		.name = "Environment Map",
		.data = &m_environmentMapRef,
		.hint = PropertyHint::Asset,
		});

	properties.push_back({
		.name = "Fog Color",
		.data = &fog.color,
		.hint = PropertyHint::Color
		});

	properties.push_back({
		.name = "Fog Density",
		.data = &fog.density,
		.hint = PropertyHint::Range,
		.metaData = RangeMetaData {0, 1, 0.01f}
		});

	properties.push_back({
		.name = "Fog Min Distance",
		.data = &fog.minDistance,
		});

	properties.push_back({
		.name = "Fog Max Distance",
		.data = &fog.maxDistance,
		});

	return properties;
}

nlohmann::json GFXEngine::Core::Scene3D::serialize() const
{
	nlohmann::json data;
	data["directionalLight"] = directionalLight.serialize();
	data["fog"] = fog.serialize();
	if (m_environmentMapRef.isTypeOf<Graphics::EnvironmentMap>()) {
		auto envMap = m_environmentMapRef.get<Graphics::EnvironmentMap>();
		data["environmentMap"] = envMap ? envMap->getName() : "";
	}
	
	for (const auto& entity : m_entities) {
		nlohmann::json entityData = entity->serialize();
		data["entities"].push_back(entityData);
	}
	return data;
}

void GFXEngine::Core::Scene3D::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags)
{
	if (data.contains("directionalLight")) {
		directionalLight.deserialize(data["directionalLight"], context);
	}

	if (data.contains("fog")) {
		fog.deserialize(data["fog"], context);
	}

	if (data.contains("environmentMap")) {
		std::string envMapName = data["environmentMap"].get<std::string>();
		auto envmap = context.assets.get<GFXEngine::Graphics::EnvironmentMap>(envMapName);
		if (!envmap) {
			throw std::runtime_error("Failed to find environment map asset with name: " + envMapName);
		}
		m_environmentMapRef.set(envmap);
	}

	auto entities = data["entities"];
	for(const auto& entityData : entities) {
		std::string typeName = entityData["type"];
		std::unique_ptr<Entity> entity = context.entityFactory.createEntity(typeName);
	
		if (!entity) {
			continue;
		}

		entity->deserialize(entityData, context, flags);
		auto entityPtr = addEntity(std::move(entity));
		context.registerEntity(entityPtr->uuid, entityPtr);
	}
}

void GFXEngine::Core::Scene3D::resolveReferences(GFXEngine::SerializationContext& context)
{
	for (auto& entity : m_entities) {
		entity->resolveReferences(context);
	}
}

void GFXEngine::Core::Scene3D::getGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex) const
{
	resources[Defintions::DIRECTIONAL_LIGHT_RESOURCE] = directionalLight.getDescriptorSet(imageIndex);
	resources[Defintions::FOG_RESOURCE] = fog.getDescriptorSet(imageIndex);
}

GFXEngine::Core::Entity* GFXEngine::Core::Scene3D::instantiatePrefab(const std::filesystem::path& path, GFXEngine::SerializationContext& context)
{
	if (!std::filesystem::exists(path)) {
		throw std::runtime_error("Prefab file does not exist: " + path.string());
	}

	auto json = Utils::loadJsonFromFile(path.string());
	if (!json.contains("prefab")) {
		throw std::runtime_error("Invalid prefab file: " + path.string());
	}

	if (!json["prefab"].contains("type")) {
		throw std::runtime_error("Invalid prefab file: " + path.string());
	}

	std::string typeName = json["prefab"]["type"].get<std::string>();
	std::unique_ptr<Entity> entity = context.entityFactory.createEntity(typeName);
	if (!entity) {
		throw std::runtime_error("Unknown entity type in prefab: " + typeName);
	}
	// When instantiating a prefab, we want to generate new UUIDs for the entities to avoid conflicts with existing entities in the scene
	entity->deserialize(json["prefab"], context, SerializationFlags::RegenerateUUID);
	
	return addEntity(std::move(entity));
}