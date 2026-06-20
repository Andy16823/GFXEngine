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
			
			//************************************
			// Method:    PipelineBuilder
			// FullName:  GFXEngine::Graphics::PipelineBuilder::PipelineBuilder
			// Access:    public 
			// Returns:   
			// Qualifier: : renderer(renderer)
			// Parameter: Renderer & renderer
			//************************************
			PipelineBuilder(Renderer& renderer) : renderer(renderer) {}
			
			//************************************
			// Method:    ~PipelineBuilder
			// FullName:  GFXEngine::Graphics::PipelineBuilder::~PipelineBuilder
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~PipelineBuilder() = default;

		public:
			
			//************************************
			// Method:    addShaderStage
			// FullName:  GFXEngine::Graphics::PipelineBuilder::addShaderStage
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: const RenderShader & shader
			//************************************
			PipelineBuilder& addShaderStage(const RenderShader& shader);	// Required
			
			//************************************
			// Method:    addVertexInputBinding
			// FullName:  GFXEngine::Graphics::PipelineBuilder::addVertexInputBinding
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: uint32_t binding
			// Parameter: uint32_t stride
			//************************************
			PipelineBuilder& addVertexInputBinding(uint32_t binding, uint32_t stride); // Required
			
			//************************************
			// Method:    addVertexInputAttribute
			// FullName:  GFXEngine::Graphics::PipelineBuilder::addVertexInputAttribute
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: uint32_t binding
			// Parameter: uint32_t location
			// Parameter: VkFormat format
			// Parameter: uint32_t offset
			//************************************
			PipelineBuilder& addVertexInputAttribute(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset); // Required

			//************************************
			// Method:    useVertex3DInput
			// FullName:  GFXEngine::Graphics::PipelineBuilder::useVertex3DInput
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: uint32_t binding
			//************************************
			PipelineBuilder& useVertex3DInput(uint32_t binding);
			
			//************************************
			// Method:    useVertex2DInput
			// FullName:  GFXEngine::Graphics::PipelineBuilder::useVertex2DInput
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: uint32_t binding
			//************************************
			PipelineBuilder& useVertex2DInput(uint32_t binding);
			
			//************************************
			// Method:    usePositionInput
			// FullName:  GFXEngine::Graphics::PipelineBuilder::usePositionInput
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: uint32_t binding
			//************************************
			PipelineBuilder& usePositionInput(uint32_t binding);
			
			//************************************
			// Method:    useFramebufferInput
			// FullName:  GFXEngine::Graphics::PipelineBuilder::useFramebufferInput
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: uint32_t binding
			//************************************
			PipelineBuilder& useFramebufferInput(uint32_t binding);

			//************************************
			// Method:    setTopology
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setTopology
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkPrimitiveTopology topology
			//************************************
			PipelineBuilder& setTopology(VkPrimitiveTopology topology);

			//************************************
			// Method:    setPolygonMode
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setPolygonMode
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkPolygonMode polygonMode
			//************************************
			PipelineBuilder& setPolygonMode(VkPolygonMode polygonMode);
			
			//************************************
			// Method:    setCullMode
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setCullMode
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkCullModeFlags cullMode
			//************************************
			PipelineBuilder& setCullMode(VkCullModeFlags cullMode);
			
			//************************************
			// Method:    setFrontFace
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setFrontFace
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkFrontFace frontFace
			//************************************
			PipelineBuilder& setFrontFace(VkFrontFace frontFace);
			
			//************************************
			// Method:    setColorWriteMask
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setColorWriteMask
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkColorComponentFlags colorWriteMask
			//************************************
			PipelineBuilder& setColorWriteMask(VkColorComponentFlags colorWriteMask);
			
			//************************************
			// Method:    setBlendEnable
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setBlendEnable
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkBool32 blendEnable
			//************************************
			PipelineBuilder& setBlendEnable(VkBool32 blendEnable);
			
			//************************************
			// Method:    setColorBlendFactors
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setColorBlendFactors
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkBlendFactor srcColorBlendFactor
			// Parameter: VkBlendFactor dstColorBlendFactor
			// Parameter: VkBlendOp colorBlendOp
			//************************************
			PipelineBuilder& setColorBlendFactors(VkBlendFactor srcColorBlendFactor, VkBlendFactor dstColorBlendFactor, VkBlendOp colorBlendOp);
			
			//************************************
			// Method:    setAlphaBlendFactors
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setAlphaBlendFactors
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkBlendFactor srcAlphaBlendFactor
			// Parameter: VkBlendFactor dstAlphaBlendFactor
			// Parameter: VkBlendOp alphaBlendOp
			//************************************
			PipelineBuilder& setAlphaBlendFactors(VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor, VkBlendOp alphaBlendOp);
			
			//************************************
			// Method:    enableAlphaBlending
			// FullName:  GFXEngine::Graphics::PipelineBuilder::enableAlphaBlending
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			//************************************
			PipelineBuilder& enableAlphaBlending();
			
			//************************************
			// Method:    enableAdditiveBlending
			// FullName:  GFXEngine::Graphics::PipelineBuilder::enableAdditiveBlending
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			//************************************
			PipelineBuilder& enableAdditiveBlending();
			
			//************************************
			// Method:    disableBlending
			// FullName:  GFXEngine::Graphics::PipelineBuilder::disableBlending
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			//************************************
			PipelineBuilder& disableBlending();

			//************************************
			// Method:    addDescriptorSetLayout
			// FullName:  GFXEngine::Graphics::PipelineBuilder::addDescriptorSetLayout
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkDescriptorSetLayout layout
			//************************************
			PipelineBuilder& addDescriptorSetLayout(VkDescriptorSetLayout layout);
			
			//************************************
			// Method:    addPushConstantRange
			// FullName:  GFXEngine::Graphics::PipelineBuilder::addPushConstantRange
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkShaderStageFlags stageFlags
			// Parameter: uint32_t offset
			// Parameter: uint32_t size
			//************************************
			PipelineBuilder& addPushConstantRange(VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size);

			//************************************
			// Method:    setDepthTestEnable
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setDepthTestEnable
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkBool32 depthTestEnable
			//************************************
			PipelineBuilder& setDepthTestEnable(VkBool32 depthTestEnable);
			
			//************************************
			// Method:    setDepthWriteEnable
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setDepthWriteEnable
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkBool32 depthWriteEnable
			//************************************
			PipelineBuilder& setDepthWriteEnable(VkBool32 depthWriteEnable);
			
			//************************************
			// Method:    setDepthCompareOp
			// FullName:  GFXEngine::Graphics::PipelineBuilder::setDepthCompareOp
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PipelineBuilder&
			// Qualifier:
			// Parameter: VkCompareOp depthCompareOp
			//************************************
			PipelineBuilder& setDepthCompareOp(VkCompareOp depthCompareOp);

			//************************************
			// Method:    buildGraphicsPipeline
			// FullName:  GFXEngine::Graphics::PipelineBuilder::buildGraphicsPipeline
			// Access:    public 
			// Returns:   std::unique_ptr<GFXEngine::Graphics::GraphicsPipeline>
			// Qualifier:
			// Parameter: VkRenderPass renderPass
			// Parameter: std::unique_ptr<IGraphicsPass> graphicsPass
			//************************************
			std::unique_ptr<GraphicsPipeline> buildGraphicsPipeline(VkRenderPass renderPass, std::unique_ptr<IGraphicsPass> graphicsPass);
			
			//************************************
			// Method:    buildPresentPipeline
			// FullName:  GFXEngine::Graphics::PipelineBuilder::buildPresentPipeline
			// Access:    public 
			// Returns:   std::unique_ptr<GFXEngine::Graphics::PresentPipeline>
			// Qualifier:
			// Parameter: VkRenderPass renderPass
			//************************************
			std::unique_ptr<PresentPipeline> buildPresentPipeline(VkRenderPass renderPass);
			
			//************************************
			// Method:    clear
			// FullName:  GFXEngine::Graphics::PipelineBuilder::clear
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void clear();
		};
	}
}