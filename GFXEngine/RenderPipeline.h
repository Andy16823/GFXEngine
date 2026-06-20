#pragma once
#include "VkContext.h"

namespace GFXEngine {
	namespace Graphics {

		class RenderPipeline {

		private:
			static inline uint64_t s_nextId = 1;
			uint64_t m_pipelineId;

		public:

			//************************************
			// Method:    RenderPipeline
			// FullName:  GFXEngine::Graphics::RenderPipeline::RenderPipeline
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			RenderPipeline()
			{
				m_pipelineId = s_nextId++;
			}
			
			//************************************
			// Method:    ~RenderPipeline
			// FullName:  GFXEngine::Graphics::RenderPipeline::~RenderPipeline
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~RenderPipeline() = default;

			//************************************
			// Method:    getId
			// FullName:  GFXEngine::Graphics::RenderPipeline::getId
			// Access:    public 
			// Returns:   uint64_t
			// Qualifier: const
			//************************************
			uint64_t getId() const
			{
				return m_pipelineId;
			}

			//************************************
			// Method:    getPipelineLayout
			// FullName:  GFXEngine::Graphics::RenderPipeline::getPipelineLayout
			// Access:    virtual public 
			// Returns:   VkPipelineLayout
			// Qualifier: const
			//************************************
			virtual VkPipelineLayout getPipelineLayout() const = 0;
			
			//************************************
			// Method:    getPipeline
			// FullName:  GFXEngine::Graphics::RenderPipeline::getPipeline
			// Access:    virtual public 
			// Returns:   VkPipeline
			// Qualifier: const
			//************************************
			virtual VkPipeline getPipeline() const = 0;

			//************************************
			// Method:    bindViewport
			// FullName:  GFXEngine::Graphics::RenderPipeline::bindViewport
			// Access:    virtual public 
			// Returns:   void
			// Qualifier: const
			// Parameter: VkCommandBuffer commandBuffer
			// Parameter: const VkViewport & viewport
			//************************************
			virtual void bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const = 0;
			
			//************************************
			// Method:    bindScissor
			// FullName:  GFXEngine::Graphics::RenderPipeline::bindScissor
			// Access:    virtual public 
			// Returns:   void
			// Qualifier: const
			// Parameter: VkCommandBuffer commandBuffer
			// Parameter: const VkRect2D & scissor
			//************************************
			virtual void bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const = 0;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::RenderPipeline::destroy
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::VkContext & context
			//************************************
			virtual void destroy(LibGFX::VkContext& context) = 0;
		};
	}
}