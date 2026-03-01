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
	if (!isVisible())
		return;

	// Call base render to handle any common rendering setup
	Entity::render(renderer, camera, imageIndex);

	// Bind pipeline to use for rendering the sprite
	renderer.usePipeline(m_pipeline, imageIndex);

	// Bind uniform buffers for camera data
	VkDescriptorSet cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
	renderer.bindDescriptorSet(cameraDescriptorSet, m_pipeline.getPipelineLayout(), 0, imageIndex);

	// Bind material descriptor sets
	m_material.bind(renderer, m_pipeline.getPipelineLayout(), imageIndex, 1);
	glm::mat4 model = transform.getModelMatrix();

	// Bind push constants for the model matrix
	renderer.bindPushConstants(&model, sizeof(glm::mat4), m_pipeline.getPipelineLayout(), imageIndex);
	m_mesh.draw(renderer, imageIndex);
}

void GFXEngine::Core::Sprite::destroy(GFXEngine::Graphics::Renderer& renderer)
{
	Entity::destroy(renderer);
}