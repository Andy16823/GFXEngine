#pragma once
#include <vulkan/vulkan.h>
#include <unordered_map>

namespace GFXEngine {
	namespace Graphics {
		
		class Renderer;
		class RenderContext;
		class Mesh;
		class Material;
		class RenderTaskBuilder;

		class IGraphicsPass 
		{
		public:
			using GraphicResources = std::unordered_map<unsigned int, VkDescriptorSet>; 
			virtual ~IGraphicsPass() = default;
			virtual VkPipelineLayout buildLayout(Renderer& renderer) const = 0;
			virtual bool buildRenderTask(RenderContext& context, const Material& material, RenderTaskBuilder& builder, GraphicResources& resources) const = 0;
		};
	}
}