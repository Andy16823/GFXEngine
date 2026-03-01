#include "Model.h"

void GFXEngine::Core::Model::render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (!isVisible())
		return;

	Entity::render(renderer, camera, imageIndex);

	// Bind pipeline to use for rendering the model
	renderer.usePipeline(m_pipeline, imageIndex);

	// Bind uniform buffers for camera data
	VkDescriptorSet cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
	renderer.bindDescriptorSet(cameraDescriptorSet, m_pipeline.getPipelineLayout(), 0, imageIndex);

	// Pass model matrix as push constant
	const glm::mat4 modelMatrix = transform.getModelMatrix();
	auto callback = [&modelMatrix](GFXEngine::Graphics::Renderer& renderer, VkPipelineLayout pipelineLayout, uint32_t imageIndex, uint32_t meshIndex) {
		renderer.bindPushConstants(&modelMatrix, sizeof(glm::mat4), pipelineLayout, imageIndex);
		};

	// Draw the mesh model, passing the callback to bind push constants for each mesh
	m_meshModel.draw(renderer, imageIndex, m_pipeline.getPipelineLayout(), callback);
}