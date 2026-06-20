#pragma once
#include "RenderPipeline.h"

namespace GFXEngine {
	namespace Graphics {
		
		class PresentPipeline : public RenderPipeline
		{
		private:
			VkPipeline m_pipeline = VK_NULL_HANDLE;
			VkPipelineLayout m_pipelineLayout = VK_NULL_HANDLE;

		public:
			//************************************
			// Method:    PresentPipeline
			// FullName:  GFXEngine::Graphics::PresentPipeline::PresentPipeline
			// Access:    public 
			// Returns:   
			// Qualifier: : m_pipeline(pipeline), m_pipelineLayout(layout)
			// Parameter: VkPipeline pipeline
			// Parameter: VkPipelineLayout layout
			//************************************
			PresentPipeline(VkPipeline pipeline, VkPipelineLayout layout) : m_pipeline(pipeline), m_pipelineLayout(layout) {}

			//************************************
			// Method:    getPipelineLayout
			// FullName:  GFXEngine::Graphics::PresentPipeline::getPipelineLayout
			// Access:    public 
			// Returns:   VkPipelineLayout
			// Qualifier: const 
			//************************************
			VkPipelineLayout getPipelineLayout() const override
			{
				return m_pipelineLayout;
			}

			//************************************
			// Method:    getPipeline
			// FullName:  GFXEngine::Graphics::PresentPipeline::getPipeline
			// Access:    public 
			// Returns:   VkPipeline
			// Qualifier: const 
			//************************************
			VkPipeline getPipeline() const override
			{
				return m_pipeline;
			}

			//************************************
			// Method:    bindViewport
			// FullName:  GFXEngine::Graphics::PresentPipeline::bindViewport
			// Access:    public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: VkCommandBuffer commandBuffer
			// Parameter: const VkViewport & viewport
			//************************************
			void bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const override;
			
			//************************************
			// Method:    bindScissor
			// FullName:  GFXEngine::Graphics::PresentPipeline::bindScissor
			// Access:    public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: VkCommandBuffer commandBuffer
			// Parameter: const VkRect2D & scissor
			//************************************
			void bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::PresentPipeline::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::VkContext & context
			//************************************
			void destroy(LibGFX::VkContext& context) override;
		};
	}
}