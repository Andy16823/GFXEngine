#pragma once
#include <vector>
#include "VkContext.h"
#include <string>
#include "DataTypes.h"
#include "RenderShader.h"
#include "Renderer.h"
#include "GraphicsPipeline.h"
#include "PresentPipeline.h"

namespace GFXEngine
{
	namespace Graphics
	{
		/// <summary>
		/// Convenience builder class for creating Vulkan graphics pipelines with a more user-friendly interface. 
		/// Allows configuring shader stages, vertex input state, rasterization state, color blending, pipeline layout, 
		/// and depth stencil state through a fluent API.
		/// </summary>
		class PipelineBuilder
		{
		private:
			Renderer& renderer;

			// Shader stages and vertex input state
			std::vector<VkPipelineShaderStageCreateInfo> m_shaderStages;
			std::vector<VkVertexInputBindingDescription> m_bindingDescriptions;
			std::vector<VkVertexInputAttributeDescription> m_attributeDescriptions;

			// Input assembly
			VkPrimitiveTopology m_primitiveTopology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

			// Rasterization state
			VkPolygonMode m_polygonMode = VK_POLYGON_MODE_FILL;
			VkCullModeFlags m_cullMode = VK_CULL_MODE_BACK_BIT;
			VkFrontFace m_frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;

			// Color blending state
			VkColorComponentFlags m_colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
			VkBool32 m_blendEnable = VK_TRUE;
			VkBlendFactor m_srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
			VkBlendFactor m_dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
			VkBlendOp m_colorBlendOp = VK_BLEND_OP_ADD;
			VkBlendFactor m_srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			VkBlendFactor m_dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			VkBlendOp m_alphaBlendOp = VK_BLEND_OP_ADD;

			// Pipeline layout
			std::vector<VkDescriptorSetLayout> m_descriptorSetLayouts;
			std::vector<VkPushConstantRange> m_pushConstantRanges;

			// Depth stencil state
			VkBool32 m_depthTestEnable = VK_TRUE;
			VkBool32 m_depthWriteEnable = VK_TRUE;
			VkCompareOp m_depthCompareOp = VK_COMPARE_OP_LESS;

		public:
			PipelineBuilder(Renderer& renderer) : renderer(renderer) {}
			virtual ~PipelineBuilder() = default;

			PipelineBuilder& addShaderStage(const RenderShader& shader);	// Required
			PipelineBuilder& addVertexInputBinding(uint32_t binding, uint32_t stride); // Required
			PipelineBuilder& addVertexInputAttribute(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset); // Required

			PipelineBuilder& useVertex3DInput(uint32_t binding);
			PipelineBuilder& useVertex2DInput(uint32_t binding);
			PipelineBuilder& usePositionInput(uint32_t binding);
			PipelineBuilder& useFramebufferInput(uint32_t binding);

			PipelineBuilder& setTopology(VkPrimitiveTopology topology);

			PipelineBuilder& setPolygonMode(VkPolygonMode polygonMode);
			PipelineBuilder& setCullMode(VkCullModeFlags cullMode);
			PipelineBuilder& setFrontFace(VkFrontFace frontFace);
			PipelineBuilder& setColorWriteMask(VkColorComponentFlags colorWriteMask);
			PipelineBuilder& setBlendEnable(VkBool32 blendEnable);
			PipelineBuilder& setColorBlendFactors(VkBlendFactor srcColorBlendFactor, VkBlendFactor dstColorBlendFactor, VkBlendOp colorBlendOp);
			PipelineBuilder& setAlphaBlendFactors(VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor, VkBlendOp alphaBlendOp);
			PipelineBuilder& enableAlphaBlending();
			PipelineBuilder& enableAdditiveBlending();
			PipelineBuilder& disableBlending();

			PipelineBuilder& addDescriptorSetLayout(VkDescriptorSetLayout layout);
			PipelineBuilder& addPushConstantRange(VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size);

			PipelineBuilder& setDepthTestEnable(VkBool32 depthTestEnable);
			PipelineBuilder& setDepthWriteEnable(VkBool32 depthWriteEnable);
			PipelineBuilder& setDepthCompareOp(VkCompareOp depthCompareOp);

			std::unique_ptr<GraphicsPipeline> buildGraphicsPipeline(VkRenderPass renderPass, std::unique_ptr<IGraphicsPass> graphicsPass);
			std::unique_ptr<PresentPipeline> buildPresentPipeline(VkRenderPass renderPass);
			void clear();
		};
	}
}