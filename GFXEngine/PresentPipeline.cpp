#include "PresentPipeline.h"
#include "Renderer.h"
#include "PipelineBuilder.h"

VkPipelineLayout GFXEngine::Graphics::PresentPipeline::getPipelineLayout() const
{
	return m_pipelineLayout;
}

VkPipeline GFXEngine::Graphics::PresentPipeline::getPipeline() const
{
	return m_pipeline;
}

void GFXEngine::Graphics::PresentPipeline::build(Renderer& renderer, VkRenderPass renderPass)
{
	std::array<VkDescriptorSetLayout, 1> descriptorSetLayouts{ renderer.getSamplerLayout() };
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges = nullptr;

	if (vkCreatePipelineLayout(renderer.getContext().getDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create pipeline layout");
	}

	PipelineBuilder builder(renderer);
	builder.addShaderStage(this->getShader())
		.useFramebufferInput(0)
		.setDepthTestEnable(VK_FALSE)
		.setFrontFace(VK_FRONT_FACE_CLOCKWISE)
		.disableBlending();
	m_pipeline = builder.build(renderPass, m_pipelineLayout);
}


void GFXEngine::Graphics::PresentPipeline::destroy(LibGFX::VkContext & context)
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

bool GFXEngine::Graphics::PresentPipeline::bindDescriptorSets(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources)
{
	// No descriptor sets to bind for the present pipeline, as it only uses a sampler for the framebuffer input.
	return true;
}