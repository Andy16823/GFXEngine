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

			void managePipeline(unsigned int pipelineId, std::unique_ptr<LibGFX::Pipeline> pipeline);
			void createPipelines(LibGFX::VkContext& context);
			void disposePipelines(LibGFX::VkContext& context);

			template<typename T>
			T* getPipeline(unsigned int pipelineId) const {
				auto it = m_pipelines.find(pipelineId);
				if (it != m_pipelines.end()) {
					return dynamic_cast<T*>(it->second.get());
				}
				return nullptr;
			}

		private:
			std::map<unsigned int, std::unique_ptr<LibGFX::Pipeline>> m_pipelines;
		};
	}

}
