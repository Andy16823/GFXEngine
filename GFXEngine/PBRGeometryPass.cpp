#include "PBRGeometryPass.h"
#include "Renderer.h"
#include "RenderContext.h"
#include "Material.h"
#include "RenderTask.h"
#include "EngineDefinitions.h"
#include <stdexcept>

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

VkPipelineLayout GFXEngine::Graphics::PBRGeometryPass::buildLayout(Renderer& renderer) const
{
	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	pushConstantRange.size = sizeof(glm::mat4);
	pushConstantRange.offset = 0;

	std::array<VkDescriptorSetLayout, 3> descriptorSetLayouts{ 
		renderer.getUniformBufferLayout(),
		renderer.getPBRMaterialLayout(),
		renderer.getUniformBufferLayout()
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

bool GFXEngine::Graphics::PBRGeometryPass::bindResources(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const
{
	if (!resources.contains(Defintions::CAMERA_RESOURCE)) 
	{
		throw std::runtime_error("PBRGeometryPass requires CAMERA_RESOURCE");
	}

	if (!resources.contains(Defintions::MATERIAL_RESOURCE))
	{
		throw std::runtime_error("PBRGeometryPass requires MATERIAL_RESOURCE");
	}

	if (!resources.contains(Defintions::DIRECTIONAL_LIGHT_RESOURCE))
	{
		throw std::runtime_error("PBRGeometryPass requires DIRECTIONAL_LIGHT_RESOURCE");
	}

	if (!builder.hasModelMatrix()) 
	{
		throw std::runtime_error("PBRGeometryPass requires ModelMatrix for push_constnat");
	}
	
	glm::mat4 modelMatrix = builder.getModelMatrix();
	VkDescriptorSet cameraDescriptorSet = resources[Defintions::CAMERA_RESOURCE];
	VkDescriptorSet materialDescriptorSet = resources[Defintions::MATERIAL_RESOURCE];
	VkDescriptorSet dirLightDescriptorSet = resources[Defintions::DIRECTIONAL_LIGHT_RESOURCE];

	builder.addDescriptorSet(cameraDescriptorSet, 0)
		.addDescriptorSet(materialDescriptorSet, 1)
		.addDescriptorSet(dirLightDescriptorSet, 2)
		.addPushConstant(&modelMatrix, sizeof(glm::mat4), 0);

	return true;
}
