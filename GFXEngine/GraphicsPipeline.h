#pragma once
#include "Pipeline.h"
#include "RenderShader.h"
#include <vector>
#include <span>

namespace GFXEngine {
	namespace Graphics {

		class GraphicsPipeline
		{
		public:
			GraphicsPipeline(VkPipeline pipeline, VkPipelineLayout pipelineLayout);
			GraphicsPipeline(const GraphicsPipeline&) = delete;
			GraphicsPipeline& operator=(const GraphicsPipeline&) = delete;
			GraphicsPipeline(GraphicsPipeline&&) = default;
			GraphicsPipeline& operator=(GraphicsPipeline&&) = default;

			VkPipelineLayout getPipelineLayout() const { return pipelineLayout; }
			VkPipeline getPipeline() const { return pipeline; }
			const std::string& getId() const { return id; }

			void bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const;
			void bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const;
			void destroy(LibGFX::VkContext& context);
		protected:
			VkPipeline pipeline;
			VkPipelineLayout pipelineLayout;
			std::string id;
		};
	}
}