#include "GraphicsPipeline.h"
#include "Utils.h"

GFXEngine::Graphics::GraphicsPipeline::GraphicsPipeline(VkPipeline pipeline, VkPipelineLayout pipelineLayout) : pipeline(pipeline), pipelineLayout(pipelineLayout)
{
	this->id = s_nextId++;
}

void GFXEngine::Graphics::GraphicsPipeline::bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const
{
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
}

void GFXEngine::Graphics::GraphicsPipeline::bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const
{
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void GFXEngine::Graphics::GraphicsPipeline::destroy(LibGFX::VkContext& context)
{
	if (pipeline != VK_NULL_HANDLE) {
		vkDestroyPipeline(context.getDevice(), pipeline, nullptr);
		pipeline = VK_NULL_HANDLE;
	}

	if (pipelineLayout != VK_NULL_HANDLE) {
		vkDestroyPipelineLayout(context.getDevice(), pipelineLayout, nullptr);
		pipelineLayout = VK_NULL_HANDLE;
	}
}
