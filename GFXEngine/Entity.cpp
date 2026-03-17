#include "Entity.h"
#include "Behavior.h"

void GFXEngine::Core::Entity::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	// Compute AABB based on meshes
	Math::AABB combinedAABB;
	size_t meshCount = getMeshCount();
	for (size_t i = 0; i < meshCount; ++i) {
		auto [mesh, material] = getMeshAndMaterial(i);
		Math::AABB meshAABB = mesh.computeAABB(); // Dont call this every frame, only on init or when mesh data changes
		combinedAABB = combinedAABB.unionWith(meshAABB);
	}
	setAABB(combinedAABB);

	// Initialize behaviors
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
