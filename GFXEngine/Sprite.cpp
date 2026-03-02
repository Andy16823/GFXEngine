#include "Sprite.h"
#include "Utils.h"
#include "Shapes.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;
using namespace GFXEngine::Core;
using namespace GFXEngine::Math;

void GFXEngine::Core::Sprite::init(GFXEngine::Graphics::Renderer& renderer)
{
	Entity::init(renderer);
}

void GFXEngine::Core::Sprite::update(float deltaTime)
{
	Entity::update(deltaTime);
}

void GFXEngine::Core::Sprite::render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (isVisible()) {
		Entity::render(renderer, camera, imageIndex);
	}
}

void GFXEngine::Core::Sprite::destroy(GFXEngine::Graphics::Renderer& renderer)
{
	Entity::destroy(renderer);
}

std::pair<const GFXEngine::Graphics::Mesh&, const GFXEngine::Graphics::Material&> Sprite::getMeshAndMaterial(size_t index) const
{
	if(index != 0) {
		throw std::out_of_range("Sprite only has one mesh and material");
	}
	return { m_mesh, m_material };
}
