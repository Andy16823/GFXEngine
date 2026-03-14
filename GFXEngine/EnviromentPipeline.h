#pragma once
#include "Pipeline.h"
#include "VkContext.h"
#include "RenderShader.h"

namespace GFXEngine {
	namespace Graphics {
		class EnviromentPipeline : public LibGFX::Pipeline
		{
		public:
			EnviromentPipeline(const RenderShader& shader, VkDescriptorSetLayout uniformLayout, VkDescriptorSetLayout cubemapLayout) 
				: m_shader(shader), m_uniformsLayout(uniformLayout), m_cubemapLayout(cubemapLayout) {
			}
			~EnviromentPipeline() = default;

			void create(LibGFX::VkContext& context) override;
			void destroy(LibGFX::VkContext& context) override;

			VkPipeline getPipeline() const override;
			VkPipelineLayout getPipelineLayout() const override;
			VkDescriptorSetLayout getUniformsDescriptorSetLayout() const { return m_uniformsLayout; }
			VkDescriptorSetLayout getCubemapDescriptorSetLayout() const { return m_cubemapLayout; }
		
			void setRenderPass(VkRenderPass renderPass) { m_renderPass = renderPass; }
			void setUniformsDescriptorSetLayout(VkDescriptorSetLayout layout) { m_uniformsLayout = layout; }
			void setCubemapDescriptorSetLayout(VkDescriptorSetLayout layout) { m_cubemapLayout = layout; }
			void setViewport(VkViewport viewport) { m_viewport = viewport; }
			void setScissor(VkRect2D scissor) { m_scissor = scissor; }

		private:
			VkViewport m_viewport;
			VkRect2D m_scissor;
			VkRenderPass m_renderPass = VK_NULL_HANDLE;
			VkPipeline m_pipeline = VK_NULL_HANDLE;
			VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
			VkDescriptorSetLayout m_uniformsLayout = VK_NULL_HANDLE;
			VkDescriptorSetLayout m_cubemapLayout = VK_NULL_HANDLE;
			const RenderShader& m_shader;
		};
	}
}
