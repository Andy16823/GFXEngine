#include "DebugPipeline.h"
#include "Renderer.h"
#include "PipelineBuilder.h"
#include "EngineDefinitions.h"
#include "RenderTask.h"

VkPipelineLayout GFXEngine::Graphics::DebugPipeline::getPipelineLayout() const
{
    return m_pipelineLayout;
}

VkPipeline GFXEngine::Graphics::DebugPipeline::getPipeline() const
{
	return m_pipeline;
}

void GFXEngine::Graphics::DebugPipeline::build(Renderer& renderer, VkRenderPass renderPass)
{
	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	pushConstantRange.size = sizeof(glm::mat4);
	pushConstantRange.offset = 0;

	std::array<VkDescriptorSetLayout, 1> descriptorSetLayouts{
		renderer.getUniformBufferLayout()
	};

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	pipelineLayoutInfo.pushConstantRangeCount = 1;
	pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

	if (vkCreatePipelineLayout(renderer.getContext().getDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create pipeline layout");
	}

	PipelineBuilder builder(renderer);
	builder.addShaderStage(this->getShader())
		.usePositionInput(0);
	m_pipeline = builder.build(renderPass, m_pipelineLayout);
}

void GFXEngine::Graphics::DebugPipeline::destroy(LibGFX::VkContext & context)
{
	if (m_pipeline != VK_NULL_HANDLE) {
		vkDestroyPipeline(context.getDevice(), m_pipeline, nullptr);
		m_pipeline = VK_NULL_HANDLE;
	}

	if (m_pipelineLayout != VK_NULL_HANDLE) {
		vkDestroyPipelineLayout(context.getDevice(), m_pipelineLayout, nullptr);
		m_pipelineLayout = VK_NULL_HANDLE;
	}
}

bool GFXEngine::Graphics::DebugPipeline::bindDescriptorSets(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources)
{
	if (!resources.contains(Defintions::CAMERA_RESOURCE))
	{
		throw std::runtime_error("DebugPass requires CAMERA_RESOURCE");
	}

	if (!builder.hasModelMatrix())
	{
		throw std::runtime_error("DebugPass missing ModelMatrix for push_constnat");
	}

	glm::mat4 modelMatrix = builder.getModelMatrix();
	VkDescriptorSet cameraDescriptorSet = resources[Defintions::CAMERA_RESOURCE];

	builder.addDescriptorSet(cameraDescriptorSet, 0)
		.addPushConstant(&modelMatrix, sizeof(glm::mat4), 0);

	return true;
}
