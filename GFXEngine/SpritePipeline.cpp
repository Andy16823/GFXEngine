#include "SpritePipeline.h"
#include "Renderer.h"
#include "PipelineBuilder.h"
#include "EngineDefinitions.h"
#include "RenderTask.h"

VkPipelineLayout GFXEngine::Graphics::SpritePipeline::getPipelineLayout() const
{
	return m_pipelineLayout;
}

VkPipeline GFXEngine::Graphics::SpritePipeline::getPipeline() const
{
	return m_pipeline;
}

void GFXEngine::Graphics::SpritePipeline::build(Renderer& renderer, VkRenderPass renderPass)
{
	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	pushConstantRange.size = sizeof(glm::mat4);
	pushConstantRange.offset = 0;


	std::array<VkDescriptorSetLayout, 2> descriptorSetLayouts{
		renderer.getUniformBufferLayout(), // Camera
		renderer.getSamplerLayout() // Sprite material (texture sampler)
	};

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	pipelineLayoutInfo.pushConstantRangeCount = 1;
	pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

	if (vkCreatePipelineLayout(renderer.getContext().getDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create pipeline layout");
	}

	PipelineBuilder builder(renderer);
	builder.addShaderStage(this->getShader())
		.useVertex2DInput(0);
	m_pipeline = builder.build(renderPass, m_pipelineLayout);
}

void GFXEngine::Graphics::SpritePipeline::destroy(LibGFX::VkContext & context)
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

bool GFXEngine::Graphics::SpritePipeline::bindDescriptorSets(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources)
{
	if (!resources.contains(Defintions::CAMERA_RESOURCE))
	{
		throw std::runtime_error("SpritePass requires CAMERA_RESOURCE");
	}
	VkDescriptorSet cameraSet = resources[Defintions::CAMERA_RESOURCE];

	if (!resources.contains(Defintions::MATERIAL_RESOURCE))
	{
		throw std::runtime_error("SpritePass requires MATERIAL_RESOURCE");
	}
	VkDescriptorSet materialSet = resources[Defintions::MATERIAL_RESOURCE];

	if (!builder.hasModelMatrix())
	{
		throw std::runtime_error("SpritePass requires ModelMatrix for push_constant");
	}

	glm::mat4 modelMatrix = builder.getModelMatrix();
	builder.addDescriptorSet(cameraSet, 0)
		.addDescriptorSet(materialSet, 1)
		.addPushConstant(&modelMatrix, sizeof(glm::mat4), 0);

	return true;
}
