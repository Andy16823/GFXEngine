#pragma once
#include "Pipeline.h"

namespace GFXEngine {
	namespace Graphics {
		/// <summary>
		/// Default render pipeline that can be used for basic rendering of entities.
		/// </summary>
		class DefaultRenderPipeline : public LibGFX::Pipeline {
		public:
			DefaultRenderPipeline() = default;
			virtual ~DefaultRenderPipeline() = default;
		};
	}
}