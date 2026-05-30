#pragma once
#include "RenderPipeline.h"
#include "IGraphicsPass.h"
#include <memory>

namespace GFXEngine {
	namespace Graphics {

		class GraphicsPipeline : public RenderPipeline
		{
		private:
			VkPipelineLayout m_pipelineLayout;
			VkPipeline m_pipeline;
			std::unique_ptr<IGraphicsPass> m_graphicsPass;

		public:
			GraphicsPipeline(VkPipeline pipeline, VkPipelineLayout layout, std::unique_ptr<IGraphicsPass> graphicsPass)
				: RenderPipeline(), m_pipeline(pipeline), m_pipelineLayout(layout), m_graphicsPass(std::move(graphicsPass)) {}

			VkPipelineLayout getPipelineLayout() const override 
			{
				assert(m_pipelineLayout != VK_NULL_HANDLE);
				return m_pipelineLayout;
			}

			VkPipeline getPipeline() const override
			{
				assert(m_pipeline != VK_NULL_HANDLE);
				return m_pipeline;
			}

			const IGraphicsPass& getGraphicsPass() const 
			{
				return *m_graphicsPass;
			}

			void bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const override;
			void bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const override;
			void destroy(LibGFX::VkContext& context) override;
		};
	}
}