#include "Model.h"
#include "Scene3D.h"

void GFXEngine::Core::Model::render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	if (isVisible()) {
		Entity::render(scene, renderer, camera, imageIndex);
		auto& scene3D = static_cast<Scene3D&>(scene);

		// Get related camera descriptor set
		VkDescriptorSet cameraDescriptorSet = camera.getDescriptorSet(imageIndex);
		glm::mat4 modelMatrix = this->transform.getModelMatrix();

		// Bind pipeline and camera descriptor set
		renderer.usePipeline(m_pipeline, imageIndex);
		renderer.bindDescriptorSet(cameraDescriptorSet, m_pipeline.getPipelineLayout(), CAMERA_UBO_BINDING, imageIndex);
		renderer.bindPushConstants(&modelMatrix, sizeof(glm::mat4), m_pipeline.getPipelineLayout(), imageIndex);
		scene3D.directionalLight.bind(renderer, camera, m_pipeline, LIGHTS_UBO_BINDING, imageIndex);

		// Render each mesh of the entity
		for (size_t i = 0; i < this->getMeshCount(); ++i) {
			auto [mesh, material] = this->getMeshAndMaterial(i);
			material.bind(renderer, camera, m_pipeline, imageIndex);
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
