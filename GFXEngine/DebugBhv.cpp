#include "DebugBhv.h"
#include "DataTypes.h"
#include "EngineDefinitions.h"
#include "Shapes.h"
#include "Entity.h"
#include "DebugPipeline.h"

using namespace GFXEngine::Core;
using namespace GFXEngine::Graphics;


void GFXEngine::Core::DebugBhv::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	auto entity = this->getEntity();
	auto [vertices, indices] = GFXEngine::Graphics::Shapes::createAabbVertices(entity->getAABB());
	
	VkDeviceSize vertexBufferSize = vertices.size() * sizeof(EngineTypes::PositionVertex);
	m_debugVertexBuffer = renderer.createBuffer(
		vertexBufferSize, 
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.updateBuffer(m_debugVertexBuffer, vertices.data(), vertices.size());

	VkDeviceSize indexBufferSize = indices.size() * sizeof(uint32_t);
	m_debugIndexBuffer = renderer.createBuffer(
		indexBufferSize, 
		VK_BUFFER_USAGE_INDEX_BUFFER_BIT, 
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.updateBuffer(m_debugIndexBuffer, indices.data(), indices.size());

	m_indexCount = static_cast<uint32_t>(indices.size());
}

void GFXEngine::Core::DebugBhv::update(Scene& scene, float deltaTime)
{

}

void GFXEngine::Core::DebugBhv::render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	VkDescriptorSet descriptorSet = camera.getDescriptorSet(imageIndex);
	glm::mat4 modelMatrix = getEntity()->transform.getModelMatrix();
	auto pipeline = renderer.getPipeline<DebugPipeline>(Defintions::DEBUG_PIPELINE);

	renderer.usePipeline(*pipeline, imageIndex);
	renderer.bindDescriptorSet(descriptorSet, pipeline->getPipelineLayout(), CAMERA_UBO_BINDING, imageIndex);
	renderer.bindPushConstants(&modelMatrix, sizeof(modelMatrix), pipeline->getPipelineLayout(), imageIndex);
	renderer.drawBuffers(m_debugVertexBuffer, m_debugIndexBuffer, m_indexCount, imageIndex);
}

void GFXEngine::Core::DebugBhv::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	renderer.destroyBuffer(m_debugVertexBuffer);
	renderer.destroyBuffer(m_debugIndexBuffer);
}
