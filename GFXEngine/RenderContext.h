#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "FrameContext.h"

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
            FrameContext& frameContext;
			uint32_t imageIndex;
			RenderPassIteration renderPass;
		};
	}
}