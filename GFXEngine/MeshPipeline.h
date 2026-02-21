#pragma once
#include "Pipeline.h"
#include "VkContext.h"
#include "LibGFX.h"
#include "DataTypes.h"
#include "RenderShader.h"

namespace GFXEngine {
	namespace Graphics {
		class MeshPipeline : public LibGFX::Pipeline
		{
		public:
			MeshPipeline(const RenderShader& shader) : m_shader(shader) {}
			void create(LibGFX::VkContext& context) override;
			void destroy(LibGFX::VkContext& context) override;
			void setViewport(VkViewport viewport) { m_viewport = viewport; }
			void setScissor(VkRect2D scissor) { m_scissor = scissor; }
			void setRenderPass(VkRenderPass renderPass) { m_renderPass = renderPass; }
			VkPipeline getPipeline() const override;
			VkPipelineLayout getPipelineLayout() const override;
			VkDescriptorSetLayout getUniformsDescriptorSetLayout() const { return m_uniformsLayout; }
			VkDescriptorSetLayout getTextureDescriptorSetLayout() const { return m_textureLayout; }

		private:
			VkPipelineLayout m_pipelineLayout;
			VkDescriptorSetLayout m_uniformsLayout;
			VkDescriptorSetLayout m_textureLayout;
			const RenderShader& m_shader;
			VkViewport m_viewport;
			VkRect2D m_scissor;
			VkRenderPass m_renderPass;
			VkPipeline m_pipeline;
		};
	}
}