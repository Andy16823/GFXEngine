#include "GraphicsPipeline.h"

void GFXEngine::Graphics::GraphicsPipeline::bindViewport(VkCommandBuffer commandBuffer, VkViewport viewport) const
{
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
}

void GFXEngine::Graphics::GraphicsPipeline::bindScissor(VkCommandBuffer commandBuffer, VkRect2D scissor) const
{
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}
