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
		return a.pipeline->getId() < b.pipeline->getId(); // Sort by pipeline ID to minimize pipeline switches
		});
}

void GFXEngine::Graphics::RenderQueue::execute(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex)
{
	int pipelineSwitches = 0;
	GraphicsPipeline* currentPipeline = nullptr;
	for (const auto& task : m_tasks)
	{
		if (task.pipeline != currentPipeline) {
			currentPipeline = task.pipeline;
			renderer.usePipeline(*task.pipeline, imageIndex);
			pipelineSwitches++;
		}

		// Bind descriptor sets
		for (const auto& descriptorSet : task.descriptorSets) {
			renderer.bindDescriptorSet(descriptorSet.descriptorSet, task.pipeline->getPipelineLayout(), descriptorSet.setIndex, imageIndex);
		}

		// Bind push constants
		for (const auto& pushConstant : task.pushConstants) {
			renderer.bindPushConstants(pushConstant.data.data(), pushConstant.size, pushConstant.offset, task.pipeline->getPipelineLayout(), imageIndex);
		}

		// Draw the mesh
		renderer.drawBuffers(*task.vertexBuffer, *task.indexBuffer, task.indexCount, imageIndex, task.instanceCount);
	}
	m_tasks.clear();
	std::cout << "Executed render queue with " << pipelineSwitches << " pipeline switches." << std::endl;
}
