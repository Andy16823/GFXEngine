#pragma once
#include "VkContext.h"
#include "Pipeline.h"
#include "RenderShader.h"

namespace GFXEngine
{
	namespace Graphics {
		class DefaultPipeline : public LibGFX::Pipeline
		{
		private:
			VkPipelineLayout m_pipelineLayout;
			VkPipeline m_pipeline;
			VkRenderPass m_renderPass;
			VkDescriptorSetLayout m_textureLayout;
			VkViewport m_viewport;
			VkRect2D m_scissor;
			RenderShader m_shader;

		public:
			void create(LibGFX::VkContext& context) override;
			void destroy(LibGFX::VkContext& context) override;
			VkPipeline getPipeline() const override;
			VkPipelineLayout getPipelineLayout() const override;
			VkDescriptorSetLayout getTextureDescriptorSetLayout() const { return m_textureLayout; }

			void setRenderPass(VkRenderPass renderPass) { m_renderPass = renderPass; }
			void setViewport(VkViewport viewport) { m_viewport = viewport; }
			void setScissor(VkRect2D scissor) { m_scissor = scissor; }
			void setShader(const RenderShader& shader) { m_shader = shader; }
		};
	}
}
