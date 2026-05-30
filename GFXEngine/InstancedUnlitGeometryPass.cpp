#include "InstancedUnlitGeometryPass.h"
#include "Renderer.h"
#include "RenderContext.h"
#include "Material.h"
#include "RenderTask.h"
#include "EngineDefinitions.h"
#include <stdexcept>

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

VkPipelineLayout GFXEngine::Graphics::InstancedUnlitGeometryPass::buildLayout(Renderer& renderer) const
{
	std::array<VkDescriptorSetLayout, 3> descriptorSetLayouts{
		renderer.getUniformBufferLayout(),
		renderer.getSamplerLayout(),
		renderer.getStorageBufferLayout()
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

bool GFXEngine::Graphics::InstancedUnlitGeometryPass::bindResources(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const
{
	if (!resources.contains(Defintions::CAMERA_RESOURCE))
	{
		throw std::runtime_error("InstancedUnlitGeometryPass requires CAMERA_RESOURCE");
	}

	if (!resources.contains(Defintions::MATERIAL_RESOURCE))
	{
		throw std::runtime_error("InstancedUnlitGeometryPass requires MATERIAL_RESOURCE");
	}

	if (!resources.contains(Defintions::INSTANCE_DATA_RESOURCE))
	{
		throw std::runtime_error("InstancedUnlitGeometryPass requires INSTANCE_DATA_RESOURCE");
	}

	VkDescriptorSet cameraSet = resources[Defintions::CAMERA_RESOURCE];
	VkDescriptorSet materialSet = resources[Defintions::MATERIAL_RESOURCE];
	VkDescriptorSet instanceDataSet = resources[Defintions::INSTANCE_DATA_RESOURCE];

	builder.addDescriptorSet(cameraSet, 0)
		.addDescriptorSet(materialSet, 1)
		.addDescriptorSet(instanceDataSet, 2);

	return true;
}
