#include "EnvironmentPass.h"
#include "Renderer.h"
#include "RenderTask.h"
#include "EngineDefinitions.h"
#include <stdexcept>

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

VkPipelineLayout GFXEngine::Graphics::EnvironmentPass::buildLayout(Renderer& renderer) const
{
	std::array<VkDescriptorSetLayout, 4> descriptorSetLayouts{
		renderer.getUniformBufferLayout(), // Camera
		renderer.getCubemapSamplerLayout(), // Cubemap sampler for environment map
		renderer.getUniformBufferLayout(), // Environment map UBO
		renderer.getUniformBufferLayout() // Fog UBO
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

	if (!resources.contains(Defintions::FOG_RESOURCE))
	{
		throw std::runtime_error("EnvironmentPass requires FOG_RESOURCE");
	}

	if (!resources.contains(Defintions::ENVIRONMENT_MAP_RESOURCE))
	{
		throw std::runtime_error("EnvironmentPass requires ENVIRONMENT_MAP_RESOURCE");
	}

	VkDescriptorSet cameraSet = resources[Defintions::CAMERA_RESOURCE];
	VkDescriptorSet cubemapSet = resources[Defintions::MATERIAL_RESOURCE];
	VkDescriptorSet environmentMapSet = resources[Defintions::ENVIRONMENT_MAP_RESOURCE];
	VkDescriptorSet fogSet = resources[Defintions::FOG_RESOURCE];

	builder.addDescriptorSet(cameraSet, 0)
		.addDescriptorSet(cubemapSet, 1)
		.addDescriptorSet(environmentMapSet, 2)
		.addDescriptorSet(fogSet, 3);

	return true;
}
