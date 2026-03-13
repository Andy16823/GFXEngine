#include "Scene3D.h"

void GFXEngine::Core::Scene3D::onInit(Graphics::Renderer& renderer)
{
	for (auto& entity : m_entities)
	{
		entity->init(renderer);
	}
}

void GFXEngine::Core::Scene3D::onUpdate(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex, float deltaTime)
{
	for (auto& entity : m_entities)
	{
		entity->update(deltaTime);
	}
}

void GFXEngine::Core::Scene3D::onRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	for (auto& entity : m_entities)
	{
		if (entity->isVisible()) {
			entity->render(renderer, camera, imageIndex);
		}
	}
}

void GFXEngine::Core::Scene3D::onDestroy(Graphics::Renderer& renderer)
{
	for (auto& entity : m_entities)
	{
		entity->destroy(renderer);
	}
	m_entities.clear();
}

void GFXEngine::Core::Scene3D::onInput(int key, int mods, int action)
{

}
