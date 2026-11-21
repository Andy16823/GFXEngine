#include "PBRPipeline.h"
#include "PipelineBuilder.h"
#include "EngineDefinitions.h"
#include "RenderTask.h"

VkPipelineLayout GFXEngine::Graphics::PBRPipeline::getPipelineLayout() const
{
	return m_pipelineLayout;
}

VkPipeline GFXEngine::Graphics::PBRPipeline::getPipeline() const
{
    return m_pipeline;
}

void GFXEngine::Graphics::PBRPipeline::build(Renderer& renderer, VkRenderPass renderPass)
{
	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
	pushConstantRange.size = sizeof(glm::mat4);
	pushConstantRange.offset = 0;

	std::array<VkDescriptorSetLayout, 4> descriptorSetLayouts{
		renderer.getUniformBufferLayout(), // Camera
		renderer.getPBRMaterialLayout(), // Material
		renderer.getUniformBufferLayout(), // Directional Light UBO
		renderer.getUniformBufferLayout() // Fog UBO
	};

	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	pipelineLayoutInfo.pushConstantRangeCount = 1;
	pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

	if (vkCreatePipelineLayout(renderer.getContext().getDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create pipeline layout");
	}

	PipelineBuilder builder(renderer);
	builder.addShaderStage(this->getShader())
		.useVertex3DInput(0);
	m_pipeline = builder.build(renderPass, m_pipelineLayout);
}

void GFXEngine::Graphics::PBRPipeline::destroy(LibGFX::VkContext & context)
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

bool GFXEngine::Graphics::PBRPipeline::bindDescriptorSets(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources)
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

	if (!resources.contains(Defintions::FOG_RESOURCE))
	{
		throw std::runtime_error("PBRGeometryPass requires FOG_RESOURCE");
	}

	glm::mat4 modelMatrix = builder.getModelMatrix();
	VkDescriptorSet cameraDescriptorSet = resources[Defintions::CAMERA_RESOURCE];
	VkDescriptorSet materialDescriptorSet = resources[Defintions::MATERIAL_RESOURCE];
	VkDescriptorSet dirLightDescriptorSet = resources[Defintions::DIRECTIONAL_LIGHT_RESOURCE];
	VkDescriptorSet fogDescriptorSet = resources[Defintions::FOG_RESOURCE];

	builder.addDescriptorSet(cameraDescriptorSet, 0)
		.addDescriptorSet(materialDescriptorSet, 1)
		.addDescriptorSet(dirLightDescriptorSet, 2)
		.addDescriptorSet(fogDescriptorSet, 3)
		.addPushConstant(&modelMatrix, sizeof(glm::mat4), 0);

	return true;
}
