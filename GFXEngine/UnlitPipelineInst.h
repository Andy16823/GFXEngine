#pragma once
#include "GraphicsPipeline.h"

namespace GFXEngine {
	namespace Graphics {
		class UnlitPipelineInst : public GraphicsPipeline
		{
		private:
			VkPipelineLayout m_pipelineLayout;
			VkPipeline m_pipeline;

		public:
			UnlitPipelineInst(RenderShader shader)
				: GraphicsPipeline(std::move(shader)), m_pipelineLayout(VK_NULL_HANDLE), m_pipeline(VK_NULL_HANDLE) {}

		public:
			VkPipelineLayout getPipelineLayout() const override;
			VkPipeline getPipeline() const override;
			void build(Renderer& renderer, VkRenderPass renderPass) override;
			void destroy(LibGFX::VkContext& context) override;
			bool bindDescriptorSets(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) override;
		};
	}
}
