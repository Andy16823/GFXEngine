#include "SolidColorPass.h"
#include "Renderer.h"
#include "RenderTask.h"
#include "EngineDefinitions.h"

#include <stdexcept>
#include <glm/glm.hpp>
#include <array>

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

VkPipelineLayout GFXEngine::Graphics::SolidColorPass::buildLayout(Renderer& renderer) const
{
    VkPushConstantRange pushConstants = {};
    pushConstants.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstants.size = sizeof(glm::mat4);
    pushConstants.offset = 0;

    std::array<VkDescriptorSetLayout, 2> descriptorSets{
        renderer.getUniformBufferLayout(), // Camera
        renderer.getUniformBufferLayout() // Material
    };

    VkPipelineLayoutCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    createInfo.setLayoutCount = static_cast<uint32_t>(descriptorSets.size());
    createInfo.pSetLayouts = descriptorSets.data();
    createInfo.pushConstantRangeCount = 1;
    createInfo.pPushConstantRanges = &pushConstants;

    VkPipelineLayout pipelineLayout;
    if (vkCreatePipelineLayout(renderer.getContext().getDevice(), &createInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline layout");
    }

    return pipelineLayout;
}

bool GFXEngine::Graphics::SolidColorPass::bindResources(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const
{
    if (!resources.contains(Defintions::CAMERA_RESOURCE)) {
        throw std::runtime_error("SolidColorPass requires CAMERA_RESOURCE");
    }

    if (!resources.contains(Defintions::MATERIAL_RESOURCE)) {
        throw std::runtime_error("SolidGeometryPass requires MATERIAL_RESOURCE");
    }

	if (!builder.hasModelMatrix())
	{
		throw std::runtime_error("SolidGeometryPass requires ModelMatrix for push_constnat");
	}

    glm::mat4 modelMatrix = builder.getModelMatrix();
    VkDescriptorSet cameraDescriptorSet = resources[Defintions::CAMERA_RESOURCE];
    VkDescriptorSet materialDescriptorSet = resources[Defintions::MATERIAL_RESOURCE];

    builder.addDescriptorSet(cameraDescriptorSet, 0)
        .addDescriptorSet(materialDescriptorSet, 1)
        .addPushConstant(&modelMatrix, sizeof(glm::mat4), 0);

    return true;
}
