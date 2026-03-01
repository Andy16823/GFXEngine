#pragma once
#include "Pipeline.h"
#include "VkContext.h"
#include "LibGFX.h"
#include "DataTypes.h"
#include "RenderShader.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// GeometryPipeline class that encapsulates the Vulkan graphics pipeline for rendering geometry.
		/// It provides methods to create and destroy the pipeline, set viewport and scissor, and access pipeline layouts and descriptor sets.
		/// </summary>
		class GeometryPipeline : public LibGFX::Pipeline
		{
		public:
			GeometryPipeline(const RenderShader& shader, VkDescriptorSetLayout uniformLayout, VkDescriptorSetLayout textureLayout) 
				: m_shader(shader), m_uniformsLayout(uniformLayout), m_textureLayout(textureLayout) {}

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

		private:
			VkRenderPass m_renderPass = VK_NULL_HANDLE;
			VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;
			VkDescriptorSetLayout m_uniformsLayout = VK_NULL_HANDLE;
			VkDescriptorSetLayout m_textureLayout = VK_NULL_HANDLE;
			VkPipeline m_pipeline = VK_NULL_HANDLE;
			const RenderShader& m_shader;
			VkViewport m_viewport;
			VkRect2D m_scissor;
		};
	}
}