#include "UnlitPipelineInst.h"
#include "Renderer.h"
#include "PipelineBuilder.h"
#include "EngineDefinitions.h"
#include "RenderTask.h"

VkPipelineLayout GFXEngine::Graphics::UnlitPipelineInst::getPipelineLayout() const
{
	return m_pipelineLayout;
}

VkPipeline GFXEngine::Graphics::UnlitPipelineInst::getPipeline() const
{
	return m_pipeline;
}

void GFXEngine::Graphics::UnlitPipelineInst::build(Renderer& renderer, VkRenderPass renderPass)
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

	if (vkCreatePipelineLayout(renderer.getContext().getDevice(), &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create pipeline layout");
	}

	PipelineBuilder builder(renderer);
	builder.addShaderStage(this->getShader())
		.useVertex3DInput(0);
	m_pipeline = builder.build(renderPass, m_pipelineLayout);
}

void GFXEngine::Graphics::UnlitPipelineInst::destroy(LibGFX::VkContext & context)
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

bool GFXEngine::Graphics::UnlitPipelineInst::bindDescriptorSets(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources)
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