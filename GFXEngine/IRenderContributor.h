#pragma once
#include "RenderTask.h"
#include "RenderContext.h"

namespace GFXEngine
{
	namespace Graphics
	{
		class IRenderContributor {
		public:
			virtual ~IRenderContributor() = default;
			virtual void contributeToRenderTask(RenderTaskBuilder& builder, const RenderContext& context) const = 0;
		};

	}
}