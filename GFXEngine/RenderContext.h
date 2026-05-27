#pragma once
#include "Renderer.h"
#include "Camera.h"

namespace GFXEngine
{
	namespace Graphics
	{
		/// <summary>
		/// RenderPassIteration is an enum that indicates the current iteration of the render pass, 
		/// allowing renderable objects to determine which rendering operations to perform 
		/// based on the current pass (e.g., shadow pass vs geometry pass).
		/// </summary>
		enum class RenderPassIteration {
			ShadowPass,
			GeometryPass
		};

		/// <summary>
		/// RenderContext encapsulates the necessary information for renderable objects to build their render tasks,
		/// </summary>
		struct RenderContext
		{
			Renderer& renderer;
			Camera& camera;
			uint32_t imageIndex;
			RenderPassIteration renderPass;
		};
	}
}