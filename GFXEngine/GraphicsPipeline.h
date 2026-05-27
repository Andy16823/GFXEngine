#pragma once
#include "Pipeline.h"
#include "RenderShader.h"
#include <vector>
#include <span>

namespace GFXEngine {
	namespace Graphics {

		class GraphicsPipeline
		{
		private:
			static inline uint64_t s_nextId = 1;

		public:
			GraphicsPipeline(VkPipeline pipeline, VkPipelineLayout pipelineLayout);
			GraphicsPipeline(const GraphicsPipeline&) = delete;
			GraphicsPipeline& operator=(const GraphicsPipeline&) = delete;
			GraphicsPipeline(GraphicsPipeline&&) = default;
			GraphicsPipeline& operator=(GraphicsPipeline&&) = default;

			VkPipelineLayout getPipelineLayout() const { return pipelineLayout; }
			VkPipeline getPipeline() const { return pipeline; }
			uint64_t getId() const { return id; }

			void bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const;
			void bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const;
			void destroy(LibGFX::VkContext& context);
		protected:
			VkPipeline pipeline;
			VkPipelineLayout pipelineLayout;
			uint64_t id;
		};
	}
}