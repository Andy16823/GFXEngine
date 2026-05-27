#include "Scene3D.h"
#include <fstream>
#include "Model.h"
#include "InstancedModel.h"
#include "AssetManager.h"
#include "EntityFactory.h"
#include "Utils.h"

/// <summary>
/// Initializes the scene by initializing the directional light and all entities in the scene.
/// </summary>
/// <param name="renderer"></param>
void GFXEngine::Core::Scene3D::init(Graphics::Renderer& renderer)
{
	directionalLight.init(renderer);
	for (auto& entity : m_entities)
	{
		entity->init(*this, renderer);
	}
}

/// <summary>
/// Updates the scene by updating the directional light and all entities in the scene.
/// </summary>
/// <param name="renderer"></param>
/// <param name="camera"></param>
/// <param name="imageIndex"></param>
/// <param name="deltaTime"></param>
void GFXEngine::Core::Scene3D::update(Graphics::Camera& camera, float deltaTime)
{
	for (auto& entity : m_entities)
	{
		entity->update(*this, camera, deltaTime);
	}
}

void GFXEngine::Core::Scene3D::beforeRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	// Update the directional light's uniform buffers and descriptor sets before rendering so that they are up to date when entities build their render tasks
	directionalLight.update(renderer, camera, imageIndex);

	// Create a render context to pass to entities and render contributors
	GFXEngine::Graphics::RenderContext context{
		.renderer = renderer,
		.camera = camera,
		.imageIndex = imageIndex
	};

	// Allow entities to add their render tasks to the render queue
	for (auto& entity : m_entities)
	{
		if (entity->isVisible())
		{
			entity->beforeRender(context);
		}
	}
}

/// <summary>
/// Renders the scene
/// </summary>
/// <param name="renderer"></param>
/// <param name="camera"></param>
/// <param name="imageIndex"></param>
/// <param name="injections"></param>
void GFXEngine::Core::Scene3D::render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	// Create a render context to pass to entities and render contributors
	GFXEngine::Graphics::RenderContext context{
		.renderer = renderer,
		.camera = camera,
		.imageIndex = imageIndex,
		.renderPass = Graphics::RenderPassIteration::GeometryPass
	};

	// Allow entities to add their render tasks to the render queue
	for (auto& entity : m_entities)
	{
		if (entity->isVisible())
		{
			entity->buildRenderTasks(context, m_renderQueue);
		}
	}
#
	// Allow the enviroment map to add its render tasks to the render queue if it exists
	if (auto* envMap = m_enviromentMapRef.get<Graphics::EnviromentMap>()) {
		envMap->buildRenderTasks(context, m_renderQueue);
	}

	// Create a render context to pass to entities and render contributors
	m_renderQueue.sort();
	m_renderQueue.execute(renderer, camera, imageIndex);
}

/// <summary>
/// After rendering the scene, this function can be used to perform any necessary operations such as post-processing effects or cleanup. 
/// </summary>
/// <param name="renderer"></param>
/// <param name="camera"></param>
/// <param name="imageIndex"></param>
void GFXEngine::Core::Scene3D::afterRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	// Create a render context to pass to entities and render contributors
	GFXEngine::Graphics::RenderContext context{
		.renderer = renderer,
		.camera = camera,
		.imageIndex = imageIndex
	};

	// Allow entities to add their render tasks to the render queue
	for (auto& entity : m_entities)
	{
		if (entity->isVisible())
		{
			entity->afterRender(context);
		}
	}
}

/// <summary>
/// Destroys the scene by destroying the directional light and all entities in the scene, then clearing the entity list.
/// </summary>
/// <param name="renderer"></param>
void GFXEngine::Core::Scene3D::destroy(Graphics::Renderer& renderer)
{
	directionalLight.destroy(renderer);
	for (auto& entity : m_entities)
	{
		entity->destroy(*this, renderer);
	}
	m_entities.clear();
}

/// <summary>
/// Inputs are currently not handled at the scene level, but this function can be used to handle any scene-wide input if needed in the future.
/// </summary>
/// <param name="key"></param>
/// <param name="mods"></param>
/// <param name="action"></param>
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
		.name = "Enviroment Map",
		.data = &m_enviromentMapRef,
		.hint = PropertyHint::Asset,
		});

	return properties;
}

/// <summary>
/// Serializes the scene by serializing each entity and storing its type information.
/// </summary>
/// <returns></returns>
nlohmann::json GFXEngine::Core::Scene3D::serialize() const
{
	nlohmann::json data;
	data["directionalLight"] = directionalLight.serialize();
	if (m_enviromentMapRef.isTypeOf<Graphics::EnviromentMap>()) {
		auto envMap = m_enviromentMapRef.get<Graphics::EnviromentMap>();
		data["enviromentMap"] = envMap ? envMap->getName() : "";
	}
	

	for (const auto& entity : m_entities) {
		nlohmann::json entityData = entity->serialize();
		data["entities"].push_back(entityData);
	}
	return data;
}

/// <summary>
/// Deserializes the scene by reading each entity's type information, creating an instance of the correct type, and deserializing its data.
/// </summary>
/// <param name="data"></param>
/// <param name="context"></param>
/// <param name="flags"></param>
void GFXEngine::Core::Scene3D::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags)
{
	if (data.contains("directionalLight")) {
		directionalLight.deserialize(data["directionalLight"], context);
	}

	if (data.contains("enviromentMap")) {
		std::string envMapName = data["enviromentMap"].get<std::string>();
		auto envmap = context.assets.get<GFXEngine::Graphics::EnviromentMap>(envMapName);
		if (!envmap) {
			throw std::runtime_error("Failed to find enviroment map asset with name: " + envMapName);
		}
		m_enviromentMapRef.set(envmap);
	}

	auto entities = data["entities"];
	for(const auto& entityData : entities) {
		std::string typeName = entityData["type"];
		std::unique_ptr<Entity> entity = context.entityFactory.createEntity(typeName);
	
		if (!entity) {
			// Continue to the next entity if the type is unknown.
			continue;
		}

		entity->deserialize(entityData, context, flags);
		addEntity(std::move(entity));
	}
}

GFXEngine::Core::Entity* GFXEngine::Core::Scene3D::instantiatePrefab(const std::filesystem::path& path, GFXEngine::SerializationContext& context)
{
	// Ensure the path exists before trying to load it
	if (!std::filesystem::exists(path)) {
		throw std::runtime_error("Prefab file does not exist: " + path.string());
	}

	// Load the prefab JSON data from the file and ensure it contains the necessary "prefab" field
	auto json = Utils::loadJsonFromFile(path.string());
	if (!json.contains("prefab")) {
		throw std::runtime_error("Invalid prefab file: " + path.string());
	}

	// Ensure the prefab JSON data contains the necessary "type" field to determine which entity type to instantiate
	if (!json["prefab"].contains("type")) {
		throw std::runtime_error("Invalid prefab file: " + path.string());
	}

	std::string typeName = json["prefab"]["type"].get<std::string>();
	std::unique_ptr<Entity> entity = context.entityFactory.createEntity(typeName);
	if (!entity) {
		throw std::runtime_error("Unknown entity type in prefab: " + typeName);
	}
	entity->deserialize(json["prefab"], context, SerializationFlags::RegenerateUUID); // When instantiating a prefab, we want to generate new UUIDs for the entities to avoid conflicts with existing entities in the scene
	
	return addEntity(std::move(entity));
}