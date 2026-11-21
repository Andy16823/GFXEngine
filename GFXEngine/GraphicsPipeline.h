#pragma once
#include "RenderPipeline.h"
#include "RenderShader.h"
#include "GraphicResources.h"
#include <memory>

namespace GFXEngine {
	namespace Graphics {

		class RenderTaskBuilder;

		/// <summary>
		/// GraphicsPipeline is a specialized abstract RenderPipeline that is used for rendering graphics. 
		/// Its used for offscreen rendering.
		/// </summary>
		class GraphicsPipeline : public RenderPipeline
		{
		private:
			RenderShader m_shader;

		public:
			
			/// <summary>
			/// Creates a new GraphicsPipeline with the specified shader. The shader is moved into the pipeline, so it should not be used after this call.
			/// </summary>
			/// <param name="shader"></param>
			GraphicsPipeline(RenderShader shader) : RenderPipeline(), m_shader(std::move(shader)) {}

			/// <summary>
			/// Returns a reference to the shader used by this pipeline. The shader is owned by the pipeline, so it should not be used after the pipeline is destroyed.
			/// </summary>
			/// <returns></returns>
			RenderShader& getShader() { return m_shader; }

			/// <summary>
			/// Binds the descriptor sets to the command buffer. This is called by the renderer when the pipeline is used.
			/// </summary>
			/// <param name="builder"></param>
			/// <param name="resources"></param>
			virtual bool bindDescriptorSets(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) = 0;

			/// <summary>
			/// Binds the viewport to the command buffer. 
			/// This is called by the renderer when the pipeline is used.
			/// </summary>
			/// <param name="commandBuffer"></param>
			/// <param name="viewport"></param>
			void bindViewport(VkCommandBuffer commandBuffer, const VkViewport& viewport) const override;

			/// <summary>
			/// Binds the scissor to the command buffer. 
			/// This is called by the renderer when the pipeline is used.
			/// </summary>
			/// <param name="commandBuffer"></param>
			/// <param name="scissor"></param>
			void bindScissor(VkCommandBuffer commandBuffer, const VkRect2D& scissor) const override;
		};
	}
}