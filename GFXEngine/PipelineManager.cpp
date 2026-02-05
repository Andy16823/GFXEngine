#include "PipelineManager.h"

LibGFX::Pipeline* GFX::Graphics::PipelineManager::getPipeline(const std::string& name) const
{
	auto it = m_pipelines.find(name);
	if (it != m_pipelines.end()) {
		return it->second.get();
	}
	return nullptr;
}

void GFX::Graphics::PipelineManager::addPipeline(const std::string& name, std::unique_ptr<LibGFX::Pipeline> pipeline)
{
	m_pipelines[name] = std::move(pipeline);
}

void GFX::Graphics::PipelineManager::createPipelines(LibGFX::VkContext& context)
{
	for (auto& [name, pipeline] : m_pipelines) {
		pipeline->create(context);
	}
}

void GFX::Graphics::PipelineManager::disposePipelines(LibGFX::VkContext& context)
{
	for (auto& [name, pipeline] : m_pipelines) {
		pipeline->destroy(context);
	}
}

void GFX::Graphics::PipelineManager::addPipeline(const std::string& name, std::unique_ptr<LibGFX::Pipeline> pipeline, LibGFX::VkContext& context)
{
	pipeline->create(context);
	m_pipelines[name] = std::move(pipeline);
}
