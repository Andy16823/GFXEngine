#include "Scene3D.h"

void GFXEngine::Core::Scene3D::init(Graphics::Renderer& renderer)
{
	for (auto& entity : m_entities)
	{
		entity->init(*this, renderer);
	}

	if (m_enviromentMap) {
		m_enviromentMap->init(renderer);
	}
}

void GFXEngine::Core::Scene3D::update(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex, float deltaTime)
{
	for (auto& entity : m_entities)
	{
		entity->update(*this, deltaTime);
	}
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
	for (auto& entity : m_entities)
	{
		entity->destroy(*this, renderer);
	}
	m_entities.clear();

	if (m_enviromentMap) {
		m_enviromentMap->destroy(renderer);
	}
}

void GFXEngine::Core::Scene3D::input(int key, int mods, int action)
{

}
