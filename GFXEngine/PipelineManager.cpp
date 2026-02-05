#include "PipelineManager.h"

LibGFX::Pipeline* GFXEngine::Graphics::PipelineManager::getPipeline(const std::string& name) const
{
	auto it = m_pipelines.find(name);
	if (it != m_pipelines.end()) {
		return it->second.get();
	}
	return nullptr;
}

void GFXEngine::Graphics::PipelineManager::addPipeline(const std::string& name, std::unique_ptr<LibGFX::Pipeline> pipeline)
{
	m_pipelines[name] = std::move(pipeline);
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

void GFXEngine::Graphics::PipelineManager::addPipeline(const std::string& name, std::unique_ptr<LibGFX::Pipeline> pipeline, LibGFX::VkContext& context)
{
	pipeline->create(context);
	m_pipelines[name] = std::move(pipeline);
}
