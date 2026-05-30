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
			virtual ~IGraphicsPass() = default;
			virtual VkPipelineLayout buildLayout(Renderer& renderer) const = 0;
			virtual bool bindResources(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const = 0;
		};
	}
}