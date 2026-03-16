#pragma once
#include "PipelineManager.h"
#include "ServiceManager.h"

namespace GFXEngine {
	class Engine
	{
	public: 
		Core::ServiceManager serviceManager;
		Graphics::PipelineManager pipelineManager;

		static Engine& getInstance()
		{
			static Engine instance;
			return instance;
		}

	private:
		Engine() = default;
		~Engine() = default;

		Engine(const Engine&) = delete;
		Engine& operator=(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator=(Engine&&) = delete;
	};
}
