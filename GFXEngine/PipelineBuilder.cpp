#include "PipelineBuilder.h"
#include <stdexcept>
#include <ostream>
#include <iostream>

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

PipelineBuilder& PipelineBuilder::addShaderStage(const RenderShader& shader, const std::string& entryPoint)
{
	auto vertexShaderModule = renderer.createShaderModule(shader.vertCode);
	VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertexShaderModule;
	vertShaderStageInfo.pName = entryPoint.c_str();
	m_shaderStages.push_back(vertShaderStageInfo);

	auto fragmentShaderModule = renderer.createShaderModule(shader.fragCode);
	VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragmentShaderModule;
	fragShaderStageInfo.pName = entryPoint.c_str();
	m_shaderStages.push_back(fragShaderStageInfo);

	return *this;
}

PipelineBuilder& PipelineBuilder::addVertexInputBinding(uint32_t binding, uint32_t stride)
{
	VkVertexInputBindingDescription bindingDescription = {};
	bindingDescription.binding = binding;
	bindingDescription.stride = stride;
	// TODO: Need to allow configuring input rate (vertex vs instance) ?
	m_bindingDescriptions.push_back(bindingDescription);
	return *this;
}

PipelineBuilder& PipelineBuilder::addVertexInputAttribute(uint32_t binding, uint32_t location, VkFormat format, uint32_t offset)
{
	VkVertexInputAttributeDescription attributeDescription = {};
	attributeDescription.binding = binding;
	attributeDescription.location = location;
	attributeDescription.format = format;
	attributeDescription.offset = offset;
	m_attributeDescriptions.push_back(attributeDescription);
	return *this;
}

PipelineBuilder& PipelineBuilder::setTopology(VkPrimitiveTopology topology)
{
	m_primitiveTopology = topology;
	return *this;
}

PipelineBuilder& PipelineBuilder::setPolygonMode(VkPolygonMode polygonMode)
{
	m_polygonMode = polygonMode;
	return *this;
}

PipelineBuilder& PipelineBuilder::setCullMode(VkCullModeFlags cullMode)
{
	m_cullMode = cullMode;
	return *this;
}

PipelineBuilder& PipelineBuilder::setFrontFace(VkFrontFace frontFace)
{
	m_frontFace = frontFace;
	return *this;
}

PipelineBuilder& PipelineBuilder::setColorWriteMask(VkColorComponentFlags colorWriteMask)
{
	m_colorWriteMask = colorWriteMask;
	return *this;
}

PipelineBuilder& PipelineBuilder::setBlendEnable(VkBool32 blendEnable)
{
	m_blendEnable = blendEnable;
	return *this;
}

PipelineBuilder& PipelineBuilder::setColorBlendFactors(VkBlendFactor srcColorBlendFactor, VkBlendFactor dstColorBlendFactor, VkBlendOp colorBlendOp)
{
	m_srcColorBlendFactor = srcColorBlendFactor;
	m_dstColorBlendFactor = dstColorBlendFactor;
	m_colorBlendOp = colorBlendOp;
	return *this;
}

PipelineBuilder& PipelineBuilder::setAlphaBlendFactors(VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor, VkBlendOp alphaBlendOp)
{
	m_srcAlphaBlendFactor = srcAlphaBlendFactor;
	m_dstAlphaBlendFactor = dstAlphaBlendFactor;
	m_alphaBlendOp = alphaBlendOp;
	return *this;
}

PipelineBuilder& PipelineBuilder::addDescriptorSetLayout(VkDescriptorSetLayout layout)
{
	m_descriptorSetLayouts.push_back(layout);
	return *this;
}

PipelineBuilder& PipelineBuilder::addPushConstantRange(VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size)
{
	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = stageFlags;
	pushConstantRange.offset = offset;
	pushConstantRange.size = size;
	m_pushConstantRanges.push_back(pushConstantRange);
	return *this;
}

PipelineBuilder& PipelineBuilder::setDepthTestEnable(VkBool32 depthTestEnable)
{
	m_depthTestEnable = depthTestEnable;
	return *this;
}

PipelineBuilder& PipelineBuilder::setDepthWriteEnable(VkBool32 depthWriteEnable)
{
	m_depthWriteEnable = depthWriteEnable;
	return *this;
}

PipelineBuilder& PipelineBuilder::setDepthCompareOp(VkCompareOp depthCompareOp)
{
	m_depthCompareOp = depthCompareOp;
	return *this;
}

PipelineBuildResult PipelineBuilder::build(VkRenderPass renderPass)
{
	if (m_shaderStages.empty()) {
		throw std::runtime_error("At least one shader stage must be added to the pipeline");
	}

	if (m_bindingDescriptions.empty()) {
		throw std::runtime_error("At least one vertex input binding must be added to the pipeline");
	}

	if (m_attributeDescriptions.empty()) {
		throw std::runtime_error("At least one vertex input attribute must be added to the pipeline");
	}

	// Vertex input state
	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(m_bindingDescriptions.size());
	vertexInputInfo.pVertexBindingDescriptions = m_bindingDescriptions.data();
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(m_attributeDescriptions.size());
	vertexInputInfo.pVertexAttributeDescriptions = m_attributeDescriptions.data();

	// Input assembly state
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = m_primitiveTopology;
	inputAssembly.primitiveRestartEnable = VK_FALSE;

	// Viewport state (dynamic)
	VkPipelineViewportStateCreateInfo viewportState = {};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.scissorCount = 1;

	// Dynamic state (viewport and scissor)
	std::vector<VkDynamicState> dynamicStates = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
	VkPipelineDynamicStateCreateInfo dynamicState = {};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicState.pDynamicStates = dynamicStates.data();

	// Rasterization state
	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = m_polygonMode;
	rasterizer.cullMode = m_cullMode;
	rasterizer.frontFace = m_frontFace;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.lineWidth = 1.0f;

	// Multisampling state
	VkPipelineMultisampleStateCreateInfo multisampling = {};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	// Color blending state
	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	colorBlendAttachment.colorWriteMask = m_colorWriteMask;
	colorBlendAttachment.blendEnable = m_blendEnable;
	colorBlendAttachment.srcColorBlendFactor = m_srcColorBlendFactor;
	colorBlendAttachment.dstColorBlendFactor = m_dstColorBlendFactor;
	colorBlendAttachment.colorBlendOp = m_colorBlendOp;
	colorBlendAttachment.srcAlphaBlendFactor = m_srcAlphaBlendFactor;
	colorBlendAttachment.dstAlphaBlendFactor = m_dstAlphaBlendFactor;
	colorBlendAttachment.alphaBlendOp = m_alphaBlendOp;

	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;

	// Pipeline layout
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(m_descriptorSetLayouts.size());
	pipelineLayoutInfo.pSetLayouts = m_descriptorSetLayouts.data();
	pipelineLayoutInfo.pushConstantRangeCount = static_cast<uint32_t>(m_pushConstantRanges.size());
	pipelineLayoutInfo.pPushConstantRanges = m_pushConstantRanges.data();

	VkPipelineLayout pipelineLayout;
	if (vkCreatePipelineLayout(renderer.getContext().getDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create pipeline layout");
	}

	// Depth stencil state
	VkPipelineDepthStencilStateCreateInfo depthStencil = {};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = m_depthTestEnable;
	depthStencil.depthWriteEnable = m_depthWriteEnable;
	depthStencil.depthCompareOp = m_depthCompareOp;
	depthStencil.depthBoundsTestEnable = VK_FALSE;
	depthStencil.stencilTestEnable = VK_FALSE;

	// Pipeline create info
	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = static_cast<uint32_t>(m_shaderStages.size());
	pipelineInfo.pStages = m_shaderStages.data();
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDepthStencilState = &depthStencil;
	pipelineInfo.pDynamicState = &dynamicState;
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.renderPass = renderPass;
	pipelineInfo.subpass = 0;

	// Create the graphics pipeline
	VkPipeline pipeline;
	if (vkCreateGraphicsPipelines(renderer.getContext().getDevice(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create graphics pipeline");
	}

	// Clean up shader modules (they can be destroyed after pipeline creation)
	for (const auto& shaderStage : m_shaderStages) {
		renderer.getContext().destroyShaderModule(shaderStage.module);
	}

	// Return the created pipeline and layout
	std::cout << "Pipeline created successfully!" << std::endl;
	return { pipeline, pipelineLayout };
}

PipelineBuilder& PipelineBuilder::useVertex3DInput(uint32_t binding)
{
	this->addVertexInputBinding(binding, sizeof(GFXEngine::EngineTypes::Vertex3D));
	this->addVertexInputAttribute(binding, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GFXEngine::EngineTypes::Vertex3D, pos));
	this->addVertexInputAttribute(binding, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GFXEngine::EngineTypes::Vertex3D, color));
	this->addVertexInputAttribute(binding, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(GFXEngine::EngineTypes::Vertex3D, texCoord));
	this->addVertexInputAttribute(binding, 3, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GFXEngine::EngineTypes::Vertex3D, normal));
	this->addVertexInputAttribute(binding, 4, VK_FORMAT_R32G32B32A32_SFLOAT, offsetof(GFXEngine::EngineTypes::Vertex3D, tangent));
	return *this;
}

PipelineBuilder& PipelineBuilder::useVertex2DInput(uint32_t binding)
{
	this->addVertexInputBinding(binding, sizeof(GFXEngine::EngineTypes::Vertex2D));
	this->addVertexInputAttribute(binding, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(GFXEngine::EngineTypes::Vertex2D, pos));
	this->addVertexInputAttribute(binding, 1, VK_FORMAT_R32G32B32_SFLOAT, offsetof(GFXEngine::EngineTypes::Vertex2D, color));
	this->addVertexInputAttribute(binding, 2, VK_FORMAT_R32G32_SFLOAT, offsetof(GFXEngine::EngineTypes::Vertex2D, texCoord));
	return *this;
}

PipelineBuilder& PipelineBuilder::enableAlphaBlending()
{
	m_blendEnable = VK_TRUE;
	m_srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	m_dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	m_colorBlendOp = VK_BLEND_OP_ADD;
	m_srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	m_dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	m_alphaBlendOp = VK_BLEND_OP_ADD;
	return *this;
}

PipelineBuilder& PipelineBuilder::enableAdditiveBlending()
{
	m_blendEnable = VK_TRUE;
	m_srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
	m_dstColorBlendFactor = VK_BLEND_FACTOR_ONE;
	m_colorBlendOp = VK_BLEND_OP_ADD;
	m_srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	m_dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	m_alphaBlendOp = VK_BLEND_OP_ADD;
	return *this;
}

PipelineBuilder& PipelineBuilder::disableBlending()
{
	m_blendEnable = VK_FALSE;
	return *this;
}