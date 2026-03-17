#include "PipelineManager.h"

void GFXEngine::Graphics::PipelineManager::managePipeline(char pipelineId, std::unique_ptr<LibGFX::Pipeline> pipeline)
{
	m_pipelines[pipelineId] = std::move(pipeline);
}

void GFXEngine::Graphics::PipelineManager::createPipelines(LibGFX::VkContext& context)
{
	for (auto& [name, pipeline] : m_pipelines) {
		pipeline->create(context);
	}
}

void GFXEngine::Graphics::PipelineManager::disposePipelines(LibGFX::VkContext& context)
{
	for (auto& [name, pipeline] : m_pipelines) {
		pipeline->destroy(context);
	}
	m_pipelines.clear();
}