#include "Scene3D.h"
#include <fstream>

void GFXEngine::Core::Scene3D::init(Graphics::Renderer& renderer)
{
	directionalLight.init(renderer);
	for (auto& entity : m_entities)
	{
		entity->init(*this, renderer);
	}
}

void GFXEngine::Core::Scene3D::update(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex, float deltaTime)
{
	for (auto& entity : m_entities)
	{
		entity->update(*this, deltaTime);
	}
	directionalLight.update(renderer, camera, imageIndex);
}

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

void GFXEngine::Core::Scene3D::destroy(Graphics::Renderer& renderer)
{
	directionalLight.destroy(renderer);
	for (auto& entity : m_entities)
	{
		entity->destroy(*this, renderer);
	}
	m_entities.clear();
}

void GFXEngine::Core::Scene3D::input(int key, int mods, int action)
{

}

nlohmann::json GFXEngine::Core::Scene3D::serialize() const
{
	// Create a JSON object to hold the scene data
	nlohmann::json data;
	for (const auto& entity : m_entities) {
		nlohmann::json entityData = entity->serialize();
		entityData["type"] = typeid(*entity).name();
		data["entities"].push_back(entityData);
	}
	return data;
}

void GFXEngine::Core::Scene3D::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context)
{

}
