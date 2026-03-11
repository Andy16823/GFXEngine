#pragma once
#include "InstancedRenderPipeline.h"
#include "VkContext.h"
#include "RenderShader.h"

namespace GFXEngine {
	namespace Graphics {
		class InstancedGeometryPipeline : public InstancedRenderPipeline
		{
		public:
			InstancedGeometryPipeline(const RenderShader& shader, VkDescriptorSetLayout uniformLayout, VkDescriptorSetLayout textureLayout, VkDescriptorSetLayout instanceDataLayout) 
				: m_shader(shader), m_uniformsLayout(uniformLayout), m_textureLayout(textureLayout), m_instanceDataLayout(instanceDataLayout) {}
			void create(LibGFX::VkContext& context) override;
			void destroy(LibGFX::VkContext& context) override;
			void setViewport(VkViewport viewport) { m_viewport = viewport; }
			void setScissor(VkRect2D scissor) { m_scissor = scissor; }
			void setRenderPass(VkRenderPass renderPass) { m_renderPass = renderPass; }
			VkPipeline getPipeline() const override;
			VkPipelineLayout getPipelineLayout() const override;
			void setUniformsDescriptorSetLayout(VkDescriptorSetLayout layout) { m_uniformsLayout = layout; }
			VkDescriptorSetLayout getUniformsDescriptorSetLayout() const { return m_uniformsLayout; }
			void setTextureDescriptorSetLayout(VkDescriptorSetLayout layout) { m_textureLayout = layout; }
			VkDescriptorSetLayout getTextureDescriptorSetLayout() const { return m_textureLayout; }
			void setInstanceDataDescriptorSetLayout(VkDescriptorSetLayout layout) { m_instanceDataLayout = layout; }
			VkDescriptorSetLayout getInstanceDataDescriptorSetLayout() const { return m_instanceDataLayout; }

		private:
			VkRenderPass m_renderPass = VK_NULL_HANDLE;
			VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
			VkDescriptorSetLayout m_uniformsLayout = VK_NULL_HANDLE;
			VkDescriptorSetLayout m_textureLayout = VK_NULL_HANDLE;
			VkDescriptorSetLayout m_instanceDataLayout = VK_NULL_HANDLE;
			VkPipeline m_pipeline = VK_NULL_HANDLE;
			const RenderShader& m_shader;
			VkViewport m_viewport;
			VkRect2D m_scissor;
		};
	}
}
