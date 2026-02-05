#pragma once
#include "VkContext.h"
#include "Pipeline.h"
#include <map>
#include <string>
#include <memory>

namespace GFXEngine {
	namespace Graphics {
		class PipelineManager
		{
		public:
			PipelineManager() = default;
			~PipelineManager() = default;
			LibGFX::Pipeline* getPipeline(const std::string& name) const;
			void addPipeline(const std::string& name, std::unique_ptr<LibGFX::Pipeline> pipeline);
			void addPipeline(const std::string& name, std::unique_ptr<LibGFX::Pipeline> pipeline, LibGFX::VkContext& context);
			void createPipelines(LibGFX::VkContext& context);
			void disposePipelines(LibGFX::VkContext& context);
		private:
			std::map<std::string, std::unique_ptr<LibGFX::Pipeline>> m_pipelines;
		};
	}

}
