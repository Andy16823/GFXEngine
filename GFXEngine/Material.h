#pragma once
#include "Renderer.h"
#include "Camera.h"

namespace GFXEngine {
	namespace Graphics {
		/// <summary>
		/// Base class for materials.
		/// </summary>
		class Material {
		public:
			Material() = default;
			virtual ~Material() = default;

			Material(const Material&) = delete; // Disable copy semantics
			Material& operator=(const Material&) = delete; // Disable copy semantics
			Material(Material&&) = default; // Allow move semantics
			Material& operator=(Material&&) = default; // Allow move semantics

			virtual void init(Renderer& renderer) = 0;
			virtual void bind(Renderer& renderer, Camera& camera, uint32_t imageIndex) const = 0;
			virtual void destroy(Renderer& renderer) = 0;
			virtual VkPipelineLayout getPipelineLayout() const = 0;
			virtual const LibGFX::Pipeline& getPipeline() const = 0;
		};
	}
}