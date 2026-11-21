#pragma once
#include "GraphicsPipeline.h"

namespace GFXEngine {
	namespace Graphics {
		
		class PresentPipeline : public GraphicsPipeline
		{
		private:
			VkPipeline m_pipeline;
			VkPipelineLayout m_pipelineLayout;

		public:
			PresentPipeline(RenderShader shader)
				: GraphicsPipeline(std::move(shader)), m_pipeline(VK_NULL_HANDLE), m_pipelineLayout(VK_NULL_HANDLE) {}
		public:
			VkPipelineLayout getPipelineLayout() const override;
			VkPipeline getPipeline() const override;
			void build(Renderer& renderer, VkRenderPass renderPass) override;
			void destroy(LibGFX::VkContext& context) override;
			bool bindDescriptorSets(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) override;
		};
	}
}