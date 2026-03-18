#include "Model.h"
#include "Scene3D.h"
#include "EngineDefinitions.h"

void GFXEngine::Core::Model::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	Entity::init(scene, renderer);

	// Ensure the model is being initialized in a Scene3D context
	if (dynamic_cast<Scene3D*>(&scene) == nullptr) {
		throw std::runtime_error("Model can only be initialized in a Scene3D");
	}
}


void GFXEngine::Core::Model::render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (isVisible()) {
		Entity::render(scene, renderer, camera, imageIndex);

		auto& scene3D = static_cast<Scene3D&>(scene);

		// Get camera descriptor set and model matrix
		VkDescriptorSet cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
		glm::mat4 modelMatrix = this->transform.getModelMatrix();

		// TODO: Create an render mode flag to switch between different pipelines (e.g. wireframe, unlit, pbr, etc.)
		auto pipeline = renderer.getPipeline<Graphics::GeometryPipeline>(Defintions::GEOMETRY_PIPELINE);
		renderer.usePipeline(*pipeline, imageIndex);
		renderer.bindDescriptorSet(cameraDescriptorSet, pipeline->getPipelineLayout(), CAMERA_UBO_BINDING, imageIndex);
		renderer.bindPushConstants(&modelMatrix, sizeof(glm::mat4), pipeline->getPipelineLayout(), imageIndex);
		scene3D.directionalLight.bind(renderer, camera, *pipeline, LIGHTS_UBO_BINDING, imageIndex);

		// Render each mesh of the entity
		for (size_t i = 0; i < this->getMeshCount(); ++i) {
			auto [mesh, material] = this->getMeshAndMaterial(i);
			material.bind(renderer, camera, *pipeline, imageIndex);
			renderer.drawBuffers(mesh.getVertexBuffer(), mesh.getIndexBuffer(), mesh.getIndexCount(), imageIndex);
		}
	}
}

size_t GFXEngine::Core::Model::getMeshCount() const
{
	return m_meshModel.getMeshCount();
}

std::pair<const GFXEngine::Graphics::Mesh&, const GFXEngine::Graphics::Material&> GFXEngine::Core::Model::getMeshAndMaterial(size_t index) const
{
	if (index >= m_meshModel.getMeshCount()) {
		throw std::out_of_range("Mesh index out of range");
	}
	return { m_meshModel.getMesh(index), m_meshModel.getMeshMaterial(index) };
}