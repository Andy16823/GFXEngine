#include "Sprite.h"
#include "Utils.h"
#include "Shapes.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;
using namespace GFXEngine::Core;
using namespace GFXEngine::Math;

Sprite::Sprite(const Graphics::SpriteMaterial& material, const Graphics::Mesh& mesh) : m_material(material), m_mesh(mesh)
{
	this->transform.position = glm::vec3(0.0f);
	this->transform.rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	this->transform.scale = glm::vec3(1.0f);
}

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

	Entity::render(renderer, camera, imageIndex);
	glm::mat4 model = transform.getModelMatrix();
	m_material.bind(renderer, camera, imageIndex);
	renderer.bindPushConstants(&model, sizeof(glm::mat4), m_material.getPipelineLayout(), imageIndex);
	m_mesh.draw(renderer, imageIndex);
}

void GFXEngine::Core::Sprite::destroy(GFXEngine::Graphics::Renderer& renderer)
{
	Entity::destroy(renderer);
}