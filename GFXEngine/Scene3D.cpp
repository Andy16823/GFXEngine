#include "Scene3D.h"
#include <fstream>
#include "Model.h"
#include "InstancedModel.h"

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
void GFXEngine::Core::Scene3D::update(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex, float deltaTime)
{
	for (auto& entity : m_entities)
	{
		entity->update(*this, deltaTime);
	}
	directionalLight.update(renderer, camera, imageIndex);
}

/// <summary>
/// Renders the scene
/// </summary>
/// <param name="renderer"></param>
/// <param name="camera"></param>
/// <param name="imageIndex"></param>
void GFXEngine::Core::Scene3D::render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	for (auto& entity : m_entities)
	{
		if (entity->isVisible()) {
			entity->render(*this, renderer, camera, imageIndex);
		}
	}

	if(m_enviromentMap) {
		m_enviromentMap->render(renderer, camera, imageIndex);
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

/// <summary>
/// Serializes the scene by serializing each entity and storing its type information.
/// </summary>
/// <returns></returns>
nlohmann::json GFXEngine::Core::Scene3D::serialize() const
{
	nlohmann::json data;
	for (const auto& entity : m_entities) {
		nlohmann::json entityData = entity->serialize();
		entityData["type"] = typeid(*entity).name();
		data["entities"].push_back(entityData);
	}
	return data;
}

/// <summary>
/// Deserializes the scene by reading each entity's type information, creating an instance of the correct type, and deserializing its data.
/// </summary>
/// <param name="data"></param>
/// <param name="context"></param>
void GFXEngine::Core::Scene3D::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context)
{
	auto entities = data["entities"];
	for(const auto& entityData : entities) {
		std::string typeName = entityData["type"];
		std::unique_ptr<Entity> entity;
	
		if (typeName == typeid(GFXEngine::Core::Model).name()) {
			entity = std::make_unique<GFXEngine::Core::Model>(); 
		}
		else if (typeName == typeid(GFXEngine::Core::InstancedModel).name()) {
			continue;
		}
		else {
			continue;
		}
		entity->deserialize(entityData, context);
		addEntity(std::move(entity));
	}
}
