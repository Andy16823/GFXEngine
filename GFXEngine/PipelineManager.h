#pragma once
#include "VkContext.h"
#include "GraphicsPipeline.h"
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

			void managePipeline(unsigned int pipelineId, std::unique_ptr<GraphicsPipeline> pipeline);
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
			std::map<unsigned int, std::unique_ptr<GraphicsPipeline>> m_pipelines;
		};
	}

}
