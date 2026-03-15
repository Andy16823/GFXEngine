#pragma once
#include "Pipeline.h"
#include "VkContext.h"
#include "RenderShader.h"

namespace GFXEngine {
	namespace Graphics {
		class InstancedGeometryPipeline : public LibGFX::Pipeline
		{
		public:
			InstancedGeometryPipeline(const RenderShader& shader) 
				: m_shader(shader) {}
			void create(LibGFX::VkContext& context) override;
			void destroy(LibGFX::VkContext& context) override;
			void setViewport(VkViewport viewport) { m_viewport = viewport; }
			void setScissor(VkRect2D scissor) { m_scissor = scissor; }
			void setRenderPass(VkRenderPass renderPass) { m_renderPass = renderPass; }
			VkPipeline getPipeline() const override;
			VkPipelineLayout getPipelineLayout() const override;

			void setDescriptorSetLayouts(std::span<const VkDescriptorSetLayout> layouts) {
				m_descriptorSetLayouts.assign(layouts.begin(), layouts.end());
			}

		private:
			std::vector<VkDescriptorSetLayout> m_descriptorSetLayouts;
			VkRenderPass m_renderPass = VK_NULL_HANDLE;
			VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
			VkPipeline m_pipeline = VK_NULL_HANDLE;
			const RenderShader& m_shader;
			VkViewport m_viewport;
			VkRect2D m_scissor;
		};
	}
}
