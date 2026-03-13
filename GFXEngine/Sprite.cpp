#include "Sprite.h"
#include "Utils.h"
#include "Shapes.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;
using namespace GFXEngine::Core;
using namespace GFXEngine::Math;

void GFXEngine::Core::Sprite::init(Scene& scene,  GFXEngine::Graphics::Renderer& renderer)
{
	Entity::init(scene, renderer);
}

void GFXEngine::Core::Sprite::update(Scene& scene, float deltaTime)
{
	Entity::update(scene, deltaTime);
}

void GFXEngine::Core::Sprite::render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (isVisible()) {
		Entity::render(scene, renderer, camera, imageIndex);
	}
}

void GFXEngine::Core::Sprite::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	Entity::destroy(scene, renderer);
}

std::pair<const GFXEngine::Graphics::Mesh&, const GFXEngine::Graphics::Material&> Sprite::getMeshAndMaterial(size_t index) const
{
	if(index != 0) {
		throw std::out_of_range("Sprite only has one mesh and material");
	}
	return { m_mesh, m_material };
}
