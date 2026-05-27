#include "RenderQueue.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

void RenderQueue::addRenderTask(RenderTask task)
{
	m_tasks.push_back(std::move(task));
}

void RenderQueue::sort()
{
	std::sort(m_tasks.begin(), m_tasks.end(), [](const RenderTask& a, const RenderTask& b) {
		return a.sortingKey < b.sortingKey;
		});
}

void GFXEngine::Graphics::RenderQueue::execute(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	std::cout << "Executing Render Queue with " << m_tasks.size() << " tasks" << std::endl;
	for (const auto& task : m_tasks)
	{
		renderer.usePipeline(*task.pipeline, imageIndex);

		// Bind descriptor sets
		for (const auto& descriptorSet : task.descriptorSets) {
			renderer.bindDescriptorSet(descriptorSet.descriptorSet, task.pipeline->getPipelineLayout(), descriptorSet.setIndex, imageIndex);
		}

		// Bind push constants
		for (const auto& pushConstant : task.pushConstants) {
			renderer.bindPushConstants(pushConstant.data.data(), pushConstant.size, pushConstant.offset, task.pipeline->getPipelineLayout(), imageIndex);
		}

		// Bind material and lights if available
		if (task.material) {
			task.material->bind(renderer, camera, *task.pipeline, imageIndex);
		}
		// Draw the mesh
		renderer.drawBuffers(*task.vertexBuffer, *task.indexBuffer, task.indexCount, imageIndex, task.instanceCount);
	}
	std::cout << "Finished executing Render Queue" << std::endl;
	m_tasks.clear();
}
