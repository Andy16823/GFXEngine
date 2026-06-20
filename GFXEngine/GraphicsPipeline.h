#pragma once
#include "RenderPipeline.h"
#include "IGraphicsPass.h"
#include <memory>

namespace GFXEngine {
	namespace Graphics {

		class GraphicsPipeline : public RenderPipeline
		{
		private:
			VkPipelineLayout m_pipelineLayout;
			VkPipeline m_pipeline;
			std::unique_ptr<IGraphicsPass> m_graphicsPass;

		public:
			
			//************************************
			// Method:    GraphicsPipeline
			// FullName:  GFXEngine::Graphics::GraphicsPipeline::GraphicsPipeline
			// Access:    public 
			// Returns:   
			// Qualifier: : RenderPipeline(), m_pipeline(pipeline), m_pipelineLayout(layout), m_graphicsPass(std::move(graphicsPass))
			// Parameter: VkPipeline pipeline
			// Parameter: VkPipelineLayout layout
			// Parameter: std::unique_ptr<IGraphicsPass> graphicsPass
			//************************************
			GraphicsPipeline(VkPipeline pipeline, VkPipelineLayout layout, std::unique_ptr<IGraphicsPass> graphicsPass)
				: RenderPipeline(), m_pipeline(pipeline), m_pipelineLayout(layout), m_graphicsPass(std::move(graphicsPass)) {}

			//************************************
			// Method:    getPipelineLayout
			// FullName:  GFXEngine::Graphics::GraphicsPipeline::getPipelineLayout
			// Access:    public 
			// Returns:   VkPipelineLayout
			// Qualifier: const 
			//************************************
			VkPipelineLayout getPipelineLayout() const override 
			{
				assert(m_pipelineLayout != VK_NULL_HANDLE);
				return m_pipelineLayout;
			}

			//************************************
			// Method:    getPipeline
			// FullName:  GFXEngine::Graphics::GraphicsPipeline::getPipeline
			// Access:    public 
			// Returns:   VkPipeline
			// Qualifier: const 
			//************************************
			VkPipeline getPipeline() const override
			{
				assert(m_pipeline != VK_NULL_HANDLE);
				return m_pipeline;
			}

			//************************************
			// Method:    getGraphicsPass
			// FullName:  GFXEngine::Graphics::GraphicsPipeline::getGraphicsPass
			// Access:    public 
			// Returns:   const GFXEngine::Graphics::IGraphicsPass&
			// Qualifier: const
			//************************************
			const IGraphicsPass& getGraphicsPass() const 
			{
				return *m_graphicsPass;
			}

			//************************************
			// Method:    bindViewport
			// FullName:  GFXEngine::Graphics::GraphicsPipeline::bindViewport
			// Access:    public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: VkCommandBuffer commandBuffer
			// Parameter: const VkViewport & viewport
			//************************************
			void bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const override;
			
			//************************************
			// Method:    bindScissor
			// FullName:  GFXEngine::Graphics::GraphicsPipeline::bindScissor
			// Access:    public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: VkCommandBuffer commandBuffer
			// Parameter: const VkRect2D & scissor
			//************************************
			void bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::GraphicsPipeline::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::VkContext & context
			//************************************
			void destroy(LibGFX::VkContext& context) override;
		};
	}
}