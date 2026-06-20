#include "PresentPipeline.h"

void GFXEngine::Graphics::PresentPipeline::bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const
{
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
}

void GFXEngine::Graphics::PresentPipeline::bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const
{
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void GFXEngine::Graphics::PresentPipeline::destroy(LibGFX::VkContext& context)
{
	if (m_pipeline != VK_NULL_HANDLE) {
		vkDestroyPipeline(context.getDevice(), m_pipeline, nullptr);
		m_pipeline = VK_NULL_HANDLE;
	}

	if (m_pipelineLayout != VK_NULL_HANDLE) {
		vkDestroyPipelineLayout(context.getDevice(), m_pipelineLayout, nullptr);
		m_pipelineLayout = VK_NULL_HANDLE;
	}
}
