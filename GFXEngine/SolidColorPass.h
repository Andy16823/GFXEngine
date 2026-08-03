#pragma once
#include "IGraphicsPass.h"

namespace GFXEngine {
	namespace Graphics {
		class SolidColorPass : public IGraphicsPass
		{
			//************************************
			// Method:    buildLayout
			// FullName:  GFXEngine::Graphics::SolidColorPass::buildLayout
			// Access:    private 
			// Returns:   VkPipelineLayout
			// Qualifier: const 
			// Parameter: Renderer & renderer
			// Description: Builds the pipeline layout for the solid color pass.
			//************************************
			VkPipelineLayout buildLayout(Renderer& renderer) const override;

			//************************************
			// Method:    bindResources
			// FullName:  GFXEngine::Graphics::SolidColorPass::bindResources
			// Access:    private 
			// Returns:   bool
			// Qualifier: const 
			// Parameter: GFXEngine::Graphics::RenderTaskBuilder & builder
			// Parameter: GFXEngine::Graphics::GraphicResources & resources
			// Description: Binds the necessary resources for the solid color pass.
			//************************************
			bool bindResources(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const override;
		};
	}
}
