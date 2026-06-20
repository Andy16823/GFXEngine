#pragma once
#include "VkContext.h"
#include "RenderPipeline.h"
#include <map>
#include <string>
#include <memory>

namespace GFXEngine {
	namespace Graphics {

		class PipelineManager
		{
		private:
			std::map<unsigned int, std::unique_ptr<RenderPipeline>> m_pipelines;

		public:
			
			//************************************
			// Method:    PipelineManager
			// FullName:  GFXEngine::Graphics::PipelineManager::PipelineManager
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			PipelineManager() = default;
			
			//************************************
			// Method:    ~PipelineManager
			// FullName:  GFXEngine::Graphics::PipelineManager::~PipelineManager
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			~PipelineManager() = default;

			//************************************
			// Method:    managePipeline
			// FullName:  GFXEngine::Graphics::PipelineManager::managePipeline
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: unsigned int pipelineId
			// Parameter: std::unique_ptr<RenderPipeline> pipeline
			//************************************
			void managePipeline(unsigned int pipelineId, std::unique_ptr<RenderPipeline> pipeline);
			
			//************************************
			// Method:    disposePipelines
			// FullName:  GFXEngine::Graphics::PipelineManager::disposePipelines
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::VkContext & context
			//************************************
			void disposePipelines(LibGFX::VkContext& context);

			//************************************
			// Method:    getPipeline
			// FullName:  GFXEngine::Graphics::PipelineManager::getPipeline
			// Access:    public 
			// Returns:   T*
			// Qualifier: const
			// Parameter: unsigned int pipelineId
			//************************************
			template<typename T>
			T* getPipeline(unsigned int pipelineId) const {
				auto it = m_pipelines.find(pipelineId);
				if (it != m_pipelines.end()) {
					return dynamic_cast<T*>(it->second.get());
				}
				return nullptr;
			}
		};
	}
}
