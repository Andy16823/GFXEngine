#include "SolidColorPipeline.h"
#include "Renderer.h"
#include "PipelineBuilder.h"
#include "EngineDefinitions.h"
#include "RenderTask.h"

VkPipelineLayout GFXEngine::Graphics::SolidColorPipeline::getPipelineLayout() const
{
    return m_pipelineLayout;
}

VkPipeline GFXEngine::Graphics::SolidColorPipeline::getPipeline() const
{
    return m_pipeline;
}

void GFXEngine::Graphics::SolidColorPipeline::build(Renderer& renderer, VkRenderPass renderPass)
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

    if (vkCreatePipelineLayout(renderer.getContext().getDevice(), &createInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline layout");
    }

	PipelineBuilder builder(renderer);
    builder.addShaderStage(this->getShader())
        .useVertex3DInput(0)
        .setCullMode(VK_CULL_MODE_NONE);
	m_pipeline = builder.build(renderPass, m_pipelineLayout);
}

void GFXEngine::Graphics::SolidColorPipeline::destroy(LibGFX::VkContext & context)
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

bool GFXEngine::Graphics::SolidColorPipeline::bindDescriptorSets(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources)
{
    if (!resources.contains(Defintions::CAMERA_RESOURCE)) {
        throw std::runtime_error("SolidColorPass requires CAMERA_RESOURCE");
    }

    if (!resources.contains(Defintions::MATERIAL_RESOURCE)) {
        throw std::runtime_error("SolidColorPass requires MATERIAL_RESOURCE");
    }

    if (!builder.hasModelMatrix())
    {
        throw std::runtime_error("SolidColorPass requires ModelMatrix for push_constnat");
    }

    glm::mat4 modelMatrix = builder.getModelMatrix();
    VkDescriptorSet cameraDescriptorSet = resources[Defintions::CAMERA_RESOURCE];
    VkDescriptorSet materialDescriptorSet = resources[Defintions::MATERIAL_RESOURCE];

    builder.addDescriptorSet(cameraDescriptorSet, 0)
        .addDescriptorSet(materialDescriptorSet, 1)
        .addPushConstant(&modelMatrix, sizeof(glm::mat4), 0);

    return true;
}
