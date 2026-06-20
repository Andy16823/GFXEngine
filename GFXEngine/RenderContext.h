#pragma once
#include "Renderer.h"
#include "Camera.h"

namespace GFXEngine
{
	namespace Graphics
	{
		enum class RenderPassIteration {
			ShadowPass,
			GeometryPass
		};

		struct RenderContext
		{
			Renderer& renderer;
			Camera& camera;
			uint32_t imageIndex;
			RenderPassIteration renderPass;
		};
	}
}