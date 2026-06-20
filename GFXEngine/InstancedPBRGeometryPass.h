#pragma once
#include "IGraphicsPass.h"

namespace GFXEngine {
	namespace Graphics {
		class InstancedPBRGeometryPass : public IGraphicsPass
		{
		public:
			
			//************************************
			// Method:    buildLayout
			// FullName:  GFXEngine::Graphics::InstancedPBRGeometryPass::buildLayout
			// Access:    public 
			// Returns:   VkPipelineLayout
			// Qualifier: const 
			// Parameter: Renderer & renderer
			//************************************
			VkPipelineLayout buildLayout(Renderer& renderer) const override;
			
			//************************************
			// Method:    bindResources
			// FullName:  GFXEngine::Graphics::InstancedPBRGeometryPass::bindResources
			// Access:    public 
			// Returns:   bool
			// Qualifier: const 
			// Parameter: GFXEngine::Graphics::RenderTaskBuilder & builder
			// Parameter: GFXEngine::Graphics::GraphicResources & resources
			//************************************
			bool bindResources(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const override;
		};
	}
}
