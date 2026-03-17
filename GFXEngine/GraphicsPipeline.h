#pragma once
#include "Pipeline.h"
#include "RenderShader.h"
#include <vector>
#include <span>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Abstract base class for graphics pipelines in the GFXEngine.
		/// TODO: Change GeometryPipeline, InstancedGeometryPipeline, EnvironmentPipeline and PresentationPipeline to inherit from this class instead of directly from Pipeline.
		/// </summary>
		class GraphicsPipeline : public LibGFX::Pipeline
		{
		public:
			GraphicsPipeline(const RenderShader& shader) 
				: shader(shader), renderPass(VK_NULL_HANDLE), pipeline(VK_NULL_HANDLE), pipelineLayout(VK_NULL_HANDLE), viewport({}), scissor({}) {}

			GraphicsPipeline(const GraphicsPipeline&) = delete;
			GraphicsPipeline& operator=(const GraphicsPipeline&) = delete;

			GraphicsPipeline(GraphicsPipeline&&) = default;
			GraphicsPipeline& operator=(GraphicsPipeline&&) = default;

			VkPipelineLayout getPipelineLayout() const override { return pipelineLayout; }
			VkPipeline getPipeline() const override { return pipeline; }
			
			void setRenderPass(VkRenderPass renderPass) { this->renderPass = renderPass; }
			void setViewport(VkViewport viewport) { this->viewport = viewport; }
			void setScissor(VkRect2D scissor) { this->scissor = scissor; }
			void setDescriptorSetLayouts(std::span<const VkDescriptorSetLayout> layouts) {
				descriptorSetLayouts.assign(layouts.begin(), layouts.end());
			}

		protected:
			std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
			const RenderShader& shader;
			VkRenderPass renderPass;
			VkPipeline pipeline;
			VkPipelineLayout pipelineLayout;
			VkViewport viewport;
			VkRect2D scissor;
		};
	}
}