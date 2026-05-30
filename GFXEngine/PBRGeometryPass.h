#pragma once
#include "IGraphicsPass.h"

namespace GFXEngine {
	namespace Graphics {
		class PBRGeometryPass : public IGraphicsPass
		{
		public:
			VkPipelineLayout buildLayout(Renderer& renderer) const override;
			bool buildRenderTask(RenderContext& context, const Material& material, RenderTaskBuilder& builder, GraphicResources& resources) const override;
		};
	}
}
