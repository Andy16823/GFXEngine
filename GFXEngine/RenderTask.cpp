#include "RenderTask.h"

GFXEngine::Graphics::RenderTaskBuilder& GFXEngine::Graphics::RenderTaskBuilder::setPipeline(GFXEngine::Graphics::GraphicsPipeline* pipeline)
{
	m_task.pipeline = pipeline;
	return *this;
}

GFXEngine::Graphics::RenderTaskBuilder& GFXEngine::Graphics::RenderTaskBuilder::setVertexBuffer(const LibGFX::Buffer& vertexBuffer)
{
	m_task.vertexBuffer = &vertexBuffer;
	return *this;
}

GFXEngine::Graphics::RenderTaskBuilder& GFXEngine::Graphics::RenderTaskBuilder::setIndexBuffer(const LibGFX::Buffer& indexBuffer)
{
	m_task.indexBuffer = &indexBuffer;
	return *this;
}

GFXEngine::Graphics::RenderTaskBuilder& GFXEngine::Graphics::RenderTaskBuilder::setBuffers(const LibGFX::Buffer& vertexBuffer, const LibGFX::Buffer& indexBuffer)
{
	m_task.vertexBuffer = &vertexBuffer;
	m_task.indexBuffer = &indexBuffer;
	return *this;
}

GFXEngine::Graphics::RenderTaskBuilder& GFXEngine::Graphics::RenderTaskBuilder::setIndexCount(uint32_t indexCount)
{
	m_task.indexCount = indexCount;
	return *this;
}

GFXEngine::Graphics::RenderTaskBuilder& GFXEngine::Graphics::RenderTaskBuilder::setMesh(const GFXEngine::Graphics::Mesh* mesh)
{
	m_task.vertexBuffer = &mesh->getVertexBuffer();
	m_task.indexBuffer = &mesh->getIndexBuffer();
	m_task.indexCount = static_cast<uint32_t>(mesh->getIndexCount());
	return *this;
}

GFXEngine::Graphics::RenderTaskBuilder& GFXEngine::Graphics::RenderTaskBuilder::setModelMatrix(const glm::mat4& modelMatrix)
{
	m_task.modelMatrix = modelMatrix;
	return *this;
}

GFXEngine::Graphics::RenderTaskBuilder& GFXEngine::Graphics::RenderTaskBuilder::addDescriptorSet(const VkDescriptorSet& descriptorSet, uint32_t setIndex)
{
	m_task.descriptorSets.push_back({ descriptorSet, setIndex });
	return *this;
}

GFXEngine::Graphics::RenderTaskBuilder& GFXEngine::Graphics::RenderTaskBuilder::addPushConstant(const void* data, size_t size, size_t offset /*= 0*/)
{
	PushConstant pushConstant;
	pushConstant.data.resize(size);
	memcpy(pushConstant.data.data(), data, size);
	pushConstant.size = size;
	pushConstant.offset = offset;
	m_task.pushConstants.push_back(std::move(pushConstant));
	return *this;
}

GFXEngine::Graphics::RenderTaskBuilder& GFXEngine::Graphics::RenderTaskBuilder::setInstanceCount(uint32_t instanceCount)
{
	m_task.instanceCount = instanceCount;
	return *this;
}

GFXEngine::Graphics::RenderTask GFXEngine::Graphics::RenderTaskBuilder::build()
{
	return m_task;
}

void GFXEngine::Graphics::RenderTaskBuilder::reset()
{
	m_task = RenderTask();
}
