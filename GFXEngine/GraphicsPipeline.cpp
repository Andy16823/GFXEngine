#include "GraphicsPipeline.h"

void GFXEngine::Graphics::GraphicsPipeline::bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const
{
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
}

void GFXEngine::Graphics::GraphicsPipeline::bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const
{
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}
