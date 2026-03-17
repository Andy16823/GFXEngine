#pragma once
#include "GraphicsPipeline.h"
#include "VkContext.h"
#include "RenderShader.h"

namespace GFXEngine {
	namespace Graphics {
		class EnviromentPipeline : public GraphicsPipeline
		{
		public:
			EnviromentPipeline(const RenderShader& shader) : GraphicsPipeline(shader) {}

			void create(LibGFX::VkContext& context) override;
			void destroy(LibGFX::VkContext& context) override;
		};
	}
}
