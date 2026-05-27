#include "DebugBhv.h"
#include "DataTypes.h"
#include "EngineDefinitions.h"
#include "Shapes.h"
#include "Entity.h"
#include "GraphicsPipeline.h"
#include "RenderTask.h"


using namespace GFXEngine::Core;
using namespace GFXEngine::Graphics;


void GFXEngine::Core::DebugBhv::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	auto entity = this->getEntity();
	auto [vertices, indices] = GFXEngine::Graphics::Shapes::createAabbVertices(entity->getAABB());
	
	// Create Vertex Buffer with staging buffer
	VkDeviceSize vertexBufferSize = vertices.size() * sizeof(EngineTypes::PositionVertex);
	auto vertexStagingBuffer = renderer.createBuffer(
		vertexBufferSize, 
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT, 
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(vertexStagingBuffer, vertices.data(), vertices.size());

	m_debugVertexBuffer = renderer.createBuffer(
		vertexBufferSize, 
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, 
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.copyBuffer(vertexStagingBuffer, m_debugVertexBuffer, vertexBufferSize);
	renderer.destroyBuffer(vertexStagingBuffer);

	// Create Index Buffer with staging buffer
	VkDeviceSize indexBufferSize = indices.size() * sizeof(uint32_t);
	auto indexStagingBuffer = renderer.createBuffer(
		indexBufferSize, 
		VK_BUFFER_USAGE_TRANSFER_SRC_BIT, 
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(indexStagingBuffer, indices.data(), indices.size());

	m_debugIndexBuffer = renderer.createBuffer(
		indexBufferSize, 
		VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, 
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	renderer.copyBuffer(indexStagingBuffer, m_debugIndexBuffer, indexBufferSize);
	renderer.destroyBuffer(indexStagingBuffer);

	// Store index count for rendering
	m_indexCount = static_cast<uint32_t>(indices.size());
}

void GFXEngine::Core::DebugBhv::update(Scene& scene, GFXEngine::Graphics::Camera& camera, float deltaTime)
{

}

void GFXEngine::Core::DebugBhv::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	renderer.destroyBuffer(m_debugVertexBuffer);
	renderer.destroyBuffer(m_debugIndexBuffer);
}

void DebugBhv::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	if (!m_isEnabled)
		return;

	VkDescriptorSet descriptorSet = context.camera.getDescriptorSet(context.imageIndex);
	glm::mat4 modelMatrix = getEntity()->transform.getModelMatrix();
	auto pipeline = context.renderer.getPipeline<GraphicsPipeline>(Defintions::DEBUG_PIPELINE);

	RenderTaskBuilder taskBuilder;
	taskBuilder.setPipeline(pipeline)
		.setBuffers(m_debugVertexBuffer, m_debugIndexBuffer)
		.setIndexCount(m_indexCount)
		.addDescriptorSet(descriptorSet, CAMERA_UBO_BINDING)
		.addPushConstant(&modelMatrix, sizeof(modelMatrix));

	renderQueue.addRenderTask(taskBuilder.build());
}

std::vector<GFXEngine::Core::PropertyInfo> DebugBhv::getProperties()
{
	std::vector<PropertyInfo> properties;
	properties.push_back({ 
		.name = "Enabled",
		.data = &m_isEnabled,
	});
	return properties;
}

nlohmann::json DebugBhv::serialize() const
{
	nlohmann::json data = Behavior::serialize();
	data["enabled"] = m_isEnabled;
	return data;
}

void DebugBhv::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags)
{
	Behavior::deserialize(data, context, flags);
	m_isEnabled = data.value("enabled", true);
}