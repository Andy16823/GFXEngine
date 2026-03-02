#include "DefaultRenderBehavior.h"
#include "Entity.h"

void GFXEngine::Core::DefaultRenderBehavior::init(Graphics::Renderer& renderer)
{

}

void GFXEngine::Core::DefaultRenderBehavior::update(float deltaTime)
{

}

void GFXEngine::Core::DefaultRenderBehavior::render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	auto entity = this->getEntity();
	size_t meshCount = entity->getMeshCount();

	// Get related camera descriptor set
	VkDescriptorSet cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
	glm::mat4 modelMatrix = entity->transform.getModelMatrix();

	// Bind pipeline and camera descriptor set
	renderer.usePipeline(m_pipeline, imageIndex);
	renderer.bindDescriptorSet(cameraDescriptorSet, m_pipeline.getPipelineLayout(), 0, imageIndex);
	renderer.bindPushConstants(&modelMatrix, sizeof(glm::mat4), m_pipeline.getPipelineLayout(), imageIndex);

	// Render each mesh of the entity
	for (size_t i = 0; i < meshCount; ++i) {
		auto [mesh, material] = entity->getMeshAndMaterial(i);
		material.bind(renderer, camera, m_pipeline, imageIndex);
		renderer.drawBuffers(mesh.getVertexBuffer(), mesh.getIndexBuffer(), mesh.getIndexCount(), imageIndex);
	}
}


void GFXEngine::Core::DefaultRenderBehavior::destroy(Graphics::Renderer& renderer)
{

}
