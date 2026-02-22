#include "Model.h"

void GFXEngine::Core::Model::render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (!isVisible())
		return;

	Entity::render(renderer, camera, imageIndex);

	const glm::mat4 modelMatrix = transform.getModelMatrix();

	auto callback = [&modelMatrix](GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex, const LibGFX::Pipeline& pipeline, uint32_t meshIndex) {
		renderer.bindPushConstants(&modelMatrix, sizeof(glm::mat4), pipeline.getPipelineLayout(), imageIndex);
		};
	m_meshModel.draw(renderer, camera, imageIndex, callback);
}