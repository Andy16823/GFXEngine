#include "Model.h"

void GFXEngine::Core::Model::render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (!isVisible())
		return;

	// Call base render to handle any common rendering setup
	Entity::render(renderer, camera, imageIndex);

	const glm::mat4 modelMatrix = transform.getModelMatrix();

	// Invoke the draw function of the mesh model, passing a callback to bind push constants for each mesh
	auto callback = [&modelMatrix](const GFXEngine::Graphics::MeshModel& meshModel, GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::Camera& camera, uint32_t imageIndex, uint32_t meshIndex) {
		const auto& material = meshModel.getMeshMaterial(meshIndex);
		const auto& pipeline = material.getPipeline();
		renderer.bindPushConstants(&modelMatrix, sizeof(glm::mat4), pipeline.getPipelineLayout(), imageIndex);
		};

	// Draw the mesh model, passing the callback to bind push constants for each mesh
	m_meshModel.draw(renderer, camera, imageIndex, callback);
}