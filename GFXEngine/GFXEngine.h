#pragma once
#include "PipelineManager.h"

namespace GFXEngine {
	class Engine
	{
	public: 
		static Engine& getInstance()
		{
			static Engine instance;
			return instance;
		}

		void addPipeline(const std::string& name, std::unique_ptr<LibGFX::Pipeline> pipeline)
		{
			m_pipelineManager.addPipeline(name, std::move(pipeline));
		}

		LibGFX::Pipeline* getPipeline(const std::string& name) const
		{
			return m_pipelineManager.getPipeline(name);
		}

	private:
		Graphics::PipelineManager m_pipelineManager;

		Engine() = default;
		~Engine() = default;

		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(Engine&&) = delete;
	};
}
