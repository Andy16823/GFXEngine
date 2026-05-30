#pragma once
#include <vulkan/vulkan.h>
#include <unordered_map>

namespace GFXEngine {
	namespace Graphics {
		
		using GraphicResources = std::unordered_map<unsigned int, VkDescriptorSet>;

		class Renderer;
		struct RenderContext;
		class Material;
		class RenderTaskBuilder;

		class IGraphicsPass 
		{
		public:
			virtual ~IGraphicsPass() = default;
			virtual VkPipelineLayout buildLayout(Renderer& renderer) const = 0;
			virtual bool buildRenderTask(GFXEngine::Graphics::RenderContext& context, const GFXEngine::Graphics::Material& material, GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const = 0;
		};
	}
}