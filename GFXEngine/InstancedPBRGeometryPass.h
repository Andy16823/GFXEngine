#pragma once
#include "IGraphicsPass.h"

namespace GFXEngine {
	namespace Graphics {
		class InstancedPBRGeometryPass : public IGraphicsPass
		{
		public:
			VkPipelineLayout buildLayout(Renderer& renderer) const override;
			bool bindResources(GFXEngine::Graphics::RenderTaskBuilder& builder, GFXEngine::Graphics::GraphicResources& resources) const override;
		};
	}
}
