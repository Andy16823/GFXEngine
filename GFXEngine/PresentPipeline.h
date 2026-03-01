#pragma once
#include "VkContext.h"
#include "Pipeline.h"
#include "RenderShader.h"

namespace GFXEngine
{
	namespace Graphics {
		class PresentPipeline : public LibGFX::Pipeline
		{
		private:
			VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
			VkPipeline m_pipeline = VK_NULL_HANDLE;
			VkRenderPass m_renderPass = VK_NULL_HANDLE;
			VkDescriptorSetLayout m_textureLayout = VK_NULL_HANDLE;
			VkViewport m_viewport;
			VkRect2D m_scissor;
			const RenderShader& m_shader;

		public:
			PresentPipeline(const RenderShader& shader) : m_shader(shader), m_pipeline(VK_NULL_HANDLE), m_pipelineLayout(VK_NULL_HANDLE), m_textureLayout(VK_NULL_HANDLE) {}
			~PresentPipeline() = default;

			void create(LibGFX::VkContext& context) override;
			void destroy(LibGFX::VkContext& context) override;
			VkPipeline getPipeline() const override;
			VkPipelineLayout getPipelineLayout() const override;

			void setTextureDescriptorSetLayout(VkDescriptorSetLayout layout) { m_textureLayout = layout; }
			VkDescriptorSetLayout getTextureDescriptorSetLayout() const { return m_textureLayout; }

			void setRenderPass(VkRenderPass renderPass) { m_renderPass = renderPass; }
			void setViewport(VkViewport viewport) { m_viewport = viewport; }
			void setScissor(VkRect2D scissor) { m_scissor = scissor; }
		};
	}
}
