#include "PipelineManager.h"

void GFXEngine::Graphics::PipelineManager::managePipeline(unsigned int pipelineId, std::unique_ptr<RenderPipeline> pipeline)
{
	m_pipelines[pipelineId] = std::move(pipeline);
}

void GFXEngine::Graphics::PipelineManager::disposePipelines(LibGFX::VkContext& context)
{
	for (auto& [id, pipeline] : m_pipelines) {
		pipeline->destroy(context);
	}
	m_pipelines.clear();
}