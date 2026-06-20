#pragma once
#include <vulkan/vulkan.h>
#include "GraphicResources.h"

namespace GFXEngine {
	namespace Graphics {
		
		class Renderer;
		struct RenderContext;
		class Material;
		class RenderTaskBuilder;

		class IGraphicsPass 
		{
		public:
			
			//************************************
			// Method:    ~IGraphicsPass
			// FullName:  GFXEngine::Graphics::IGraphicsPass::~IGraphicsPass
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~IGraphicsPass() = default;
			
			//************************************
			// Method:    buildLayout
			// FullName:  GFXEngine::Graphics::IGraphicsPass::buildLayout
			// Access:    virtual public 
			// Returns:   VkPipelineLayout
			// Qualifier: const
			// Parameter: Renderer & renderer
			//************************************
			virtual VkPipelineLayout buildLayout(Renderer& renderer) const = 0;
			
			//************************************
			// Method:    bindResources
			// FullName:  GFXEngine::Graphics::IGraphicsPass::bindResources
			// Access:    virtual public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: GFXEngine::Graphics::RenderTaskBuilder & builder
			// Parameter: GFXEngine::Graphics::GraphicResources & resources
			//************************************
			virtual bool bindResources(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const = 0;
		};
	}
}