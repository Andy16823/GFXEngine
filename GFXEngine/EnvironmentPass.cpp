#include "EnvironmentPass.h"
#include "Renderer.h"
#include "RenderTask.h"
#include "EngineDefinitions.h"
#include <stdexcept>

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

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

bool GFXEngine::Graphics::EnvironmentPass::bindResources(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const
{
	if (!resources.contains(Defintions::CAMERA_RESOURCE))
	{
		throw std::runtime_error("EnvironmentPass requires CAMERA_RESOURCE");
	}

	if (!resources.contains(Defintions::MATERIAL_RESOURCE))
	{
		throw std::runtime_error("EnvironmentPass requires MATERIAL_RESOURCE");
	}

	VkDescriptorSet cameraSet = resources[Defintions::CAMERA_RESOURCE];
	VkDescriptorSet cubemapSet = resources[Defintions::MATERIAL_RESOURCE];

	builder.addDescriptorSet(cameraSet, 0)
		.addDescriptorSet(cubemapSet, 1);

	return true;
}
