#include "InstancedPBRGeometryPass.h"
#include "Renderer.h"
#include "RenderContext.h"
#include "Material.h"
#include "RenderTask.h"
#include "EngineDefinitions.h"
#include <stdexcept>

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

VkPipelineLayout GFXEngine::Graphics::InstancedPBRGeometryPass::buildLayout(Renderer& renderer) const
{
	std::array<VkDescriptorSetLayout, 4> descriptorSetLayouts{
		renderer.getUniformBufferLayout(),
		renderer.getPBRMaterialLayout(),
		renderer.getUniformBufferLayout(),
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

bool GFXEngine::Graphics::InstancedPBRGeometryPass::buildRenderTask(RenderContext& context, const Material& material, RenderTaskBuilder& builder, GraphicResources& resources) const
{
	if (!resources.contains(Defintions::DIRECTIONAL_LIGHT_RESOURCE)) 
	{
		throw std::runtime_error("InstancedPBRGeometryPass requires DIRECTIONAL_LIGHT_RESOURCE");
	}

	if (!resources.contains(Defintions::INSTANCE_DATA_SSBO))
	{
		throw std::runtime_error("InstancedPBRGeometryPass requires INSTANCE_DATA_SSBO");
	}

	VkDescriptorSet cameraSet = context.camera.getDescriptorSet(context.imageIndex);
	VkDescriptorSet materialSet = material.getDescriptorSet();
	VkDescriptorSet lightSet = resources[Defintions::DIRECTIONAL_LIGHT_RESOURCE];
	VkDescriptorSet instanceDataSet = resources[Defintions::INSTANCE_DATA_SSBO];

	builder.addDescriptorSet(cameraSet, 0)
		.addDescriptorSet(materialSet, 1)
		.addDescriptorSet(lightSet, 2)
		.addDescriptorSet(instanceDataSet, 3);

	return true;
}