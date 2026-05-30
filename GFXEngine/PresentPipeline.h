#pragma once
#include "RenderPipeline.h"

namespace GFXEngine {
	namespace Graphics {
		class PresentPipeline : public RenderPipeline
		{
		private:
			VkPipeline m_pipeline = VK_NULL_HANDLE;
			VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;

		public:
			PresentPipeline(VkPipeline pipeline, VkPipelineLayout layout) : m_pipeline(pipeline), m_pipelineLayout(layout) {}

			VkPipelineLayout getPipelineLayout() const override
			{
				return m_pipelineLayout;
			}

			VkPipeline getPipeline() const override
			{
				return m_pipeline;
			}

			void bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const override;
			void bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const override;
			void destroy(LibGFX::VkContext& context) override;
		};
	}
}