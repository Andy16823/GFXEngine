#pragma once
#include "VkContext.h"

namespace GFXEngine {
	namespace Graphics {
		class RenderPipeline {

		private:
			static inline uint64_t s_nextId = 1;
			uint64_t m_pipelineId;

		public:
			RenderPipeline()
			{
				m_pipelineId = s_nextId++;
			}
			virtual ~RenderPipeline() = default;

			uint64_t getId() const
			{
				return m_pipelineId;
			}

			virtual VkPipelineLayout getPipelineLayout() const = 0;
			virtual VkPipeline getPipeline() const = 0;

			virtual void bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const = 0;
			virtual void bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const = 0;
			virtual void destroy(LibGFX::VkContext& context) = 0;
		};
	}
}