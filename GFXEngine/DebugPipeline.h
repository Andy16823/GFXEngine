#pragma once
#include "GraphicsPipeline.h"
#include "VkContext.h"
#include <vector>

namespace GFXEngine {
	namespace Graphics {
		class DebugPipeline : public GraphicsPipeline {

		public:
			DebugPipeline(const RenderShader& shader) : GraphicsPipeline(shader) {}

			void create(LibGFX::VkContext& context) override;
			void destroy(LibGFX::VkContext& context) override;
		};
	}
}
