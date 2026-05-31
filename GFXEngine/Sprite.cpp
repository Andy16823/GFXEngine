#include "Sprite.h"
#include "Utils.h"
#include "Scene.h"
#include "Renderer.h"
#include "Camera.h"
#include "EngineDefinitions.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;
using namespace GFXEngine::Core;
using namespace GFXEngine::Math;

void GFXEngine::Core::Sprite::init(Scene& scene,  GFXEngine::Graphics::Renderer& renderer)
{
	Entity::init(scene, renderer);
}

void GFXEngine::Core::Sprite::update(Scene& scene, GFXEngine::Graphics::Camera& camera, float deltaTime)
{
	Entity::update(scene, camera, deltaTime);
}

void Sprite::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	Entity::buildRenderTasks(context, renderQueue);
	if (context.renderPass == Graphics::RenderPassIteration::GeometryPass) 
	{
		// TODO: Render Sprites!
	}
}

void GFXEngine::Core::Sprite::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	Entity::destroy(scene, renderer);
}

void Sprite::getGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const
{
	assert(meshIndex == 0); // Sprite only has one mesh and material
	const auto& material = getMeshAndMaterial(meshIndex).second;
	resources[Defintions::MATERIAL_RESOURCE] = material.getDescriptorSet(imageIndex);
}

std::pair<const GFXEngine::Graphics::Mesh&, const GFXEngine::Graphics::Material&> Sprite::getMeshAndMaterial(size_t index) const
{
	if(index != 0) {
		throw std::out_of_range("Sprite only has one mesh and material");
	}
	return { m_mesh, m_material };
}
