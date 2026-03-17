#pragma once
#include "GraphicsPipeline.h"
#include "VkContext.h"
#include "LibGFX.h"
#include "DataTypes.h"
#include "RenderShader.h"
#include <vector>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// GeometryPipeline class that encapsulates the Vulkan graphics pipeline for rendering geometry.
		/// It provides methods to create and destroy the pipeline, set viewport and scissor, and access pipeline layouts and descriptor sets.
		/// </summary>
		class GeometryPipeline : public GraphicsPipeline
		{
		public:
			GeometryPipeline(const RenderShader& shader) : GraphicsPipeline(shader) {}

			void create(LibGFX::VkContext& context) override;
			void destroy(LibGFX::VkContext& context) override;
		};
	}
}