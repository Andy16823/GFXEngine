#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "Pipeline.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Base class for materials.
		/// </summary>
		class Material {
		public:
			Material() = default;
			virtual ~Material() = default;

			Material(const Material&) = delete;
			Material& operator=(const Material&) = delete;
			Material(Material&&) = default;
			Material& operator=(Material&&) = default;

			virtual void init(Renderer& renderer) = 0;
			virtual void bind(Renderer& renderer, uint32_t imageIndex, uint32_t firstSet) const = 0;
			virtual void destroy(Renderer& renderer) = 0;

			virtual const LibGFX::Pipeline& getPipeline() const = 0;
		};
	}
}