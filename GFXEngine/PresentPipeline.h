#pragma once
#include "VkContext.h"
#include "GraphicsPipeline.h"
#include "RenderShader.h"

namespace GFXEngine
{
	namespace Graphics {
		class PresentPipeline : public GraphicsPipeline
		{
		public:
			PresentPipeline(const RenderShader& shader) : GraphicsPipeline(shader) {}

			void create(LibGFX::VkContext& context) override;
			void destroy(LibGFX::VkContext& context) override;
		};
	}
}
