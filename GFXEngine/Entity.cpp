#include "Entity.h"
#include "Behavior.h"

void GFXEngine::Core::Entity::init(GFXEngine::Graphics::Renderer& renderer)
{
	for (auto& behavior : m_behaviors) {
		behavior->init(renderer);
	}
}

void GFXEngine::Core::Entity::update(float deltaTime)
{
	for (auto& behavior : m_behaviors) {
		behavior->update(deltaTime);
	}
}

void GFXEngine::Core::Entity::render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	for (auto& behavior : m_behaviors) {
		behavior->render(renderer, camera, imageIndex);
	}
}

void GFXEngine::Core::Entity::destroy(GFXEngine::Graphics::Renderer& renderer)
{
	for (auto& behavior : m_behaviors) {
		behavior->destroy(renderer);
	}
}
