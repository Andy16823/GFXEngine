#include "UnlitGeometryPass.h"
#include "Renderer.h"
#include "EngineDefinitions.h"
#include "RenderTask.h"
#include <stdexcept>

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

VkPipelineLayout GFXEngine::Graphics::UnlitGeometryPass::buildLayout(Renderer& renderer) const
{
	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	pushConstantRange.size = sizeof(glm::mat4);
	pushConstantRange.offset = 0;

	std::array<VkDescriptorSetLayout, 2> descriptorSetLayouts{
		renderer.getUniformBufferLayout(),
		renderer.getSamplerLayout()
	};

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	pipelineLayoutInfo.pushConstantRangeCount = 1;
	pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

	VkPipelineLayout pipelineLayout;
	if (vkCreatePipelineLayout(renderer.getContext().getDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create pipeline layout");
	}
	return pipelineLayout;
}

bool GFXEngine::Graphics::UnlitGeometryPass::bindResources(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const
{
	if (!resources.contains(Defintions::CAMERA_RESOURCE))
	{
		throw std::runtime_error("UnlitGeometryPass requires CAMERA_RESOURCE");
	}

	if (!resources.contains(Defintions::MATERIAL_RESOURCE))
	{
		throw std::runtime_error("UnlitGeometryPass requires MATERIAL_RESOURCE");
	}

	if (!builder.hasModelMatrix())
	{
		throw std::runtime_error("PBRGeometryPass missing ModelMatrix for push_constnat");
	}

	glm::mat4 modelMatrix = builder.getModelMatrix();
	VkDescriptorSet cameraDescriptorSet = resources[Defintions::CAMERA_RESOURCE];
	VkDescriptorSet materialDescriptorSet = resources[Defintions::MATERIAL_RESOURCE];

	builder.addDescriptorSet(cameraDescriptorSet, 0)
		.addDescriptorSet(materialDescriptorSet, 1)
		.addPushConstant(&modelMatrix, sizeof(glm::mat4), 0);

	return true;
}