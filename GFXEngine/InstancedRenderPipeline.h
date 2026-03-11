#pragma once
#include "Pipeline.h"

namespace GFXEngine {
	namespace Graphics {
		/// <summary>
		/// Default render pipeline that uses the default render behavior.
		/// </summary>
		class InstancedRenderPipeline : public LibGFX::Pipeline {
		public:
			InstancedRenderPipeline() = default;
			~InstancedRenderPipeline() = default;
		};
	}
}