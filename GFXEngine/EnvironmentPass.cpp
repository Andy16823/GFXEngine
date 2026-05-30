#include "EnvironmentPass.h"
#include "Renderer.h"
#include "RenderContext.h"
#include "Material.h"
#include "RenderTask.h"
#include <stdexcept>

VkPipelineLayout GFXEngine::Graphics::EnvironmentPass::buildLayout(Renderer& renderer) const
{
	std::array<VkDescriptorSetLayout, 2> descriptorSetLayouts{
		renderer.getUniformBufferLayout(),
		renderer.getCubemapSamplerLayout()
	};

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges = nullptr;

	VkPipelineLayout pipelineLayout;
	if (vkCreatePipelineLayout(renderer.getContext().getDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create pipeline layout");
	}

	return pipelineLayout;
}

bool GFXEngine::Graphics::EnvironmentPass::buildRenderTask(RenderContext& context, const Material& material, RenderTaskBuilder& builder, GraphicResources& resources) const
{
	VkDescriptorSet cameraSet = context.camera.getDescriptorSet(context.imageIndex);
	VkDescriptorSet cubemapSet = material.getDescriptorSet();

	builder.addDescriptorSet(cameraSet, 0)
		.addDescriptorSet(cubemapSet, 1);

	return true;
}
