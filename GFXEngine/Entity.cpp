#include "Entity.h"
#include "Behavior.h"

void GFXEngine::Core::Entity::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	for (auto& behavior : m_behaviors) {
		behavior->init(scene, renderer);
	}
}

void GFXEngine::Core::Entity::update(Scene& scene, float deltaTime)
{
	for (auto& behavior : m_behaviors) {
		behavior->update(scene, deltaTime);
	}
}

void GFXEngine::Core::Entity::render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	for (auto& behavior : m_behaviors) {
		behavior->render(scene, renderer, camera, imageIndex);
	}
}

void GFXEngine::Core::Entity::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	for (auto& behavior : m_behaviors) {
		behavior->destroy(scene, renderer);
	}
}
