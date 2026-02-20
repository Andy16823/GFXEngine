#pragma once
#include "Renderer.h"
#include "Camera3D.h"

namespace GFXEngine {
	namespace Graphics {
		/// <summary>
		/// Base class for materials.
		/// </summary>
		class Material {
		public:
			Material() = default;
			virtual ~Material() = default;
			virtual void init(Renderer& renderer) = 0;
			virtual void bind(Renderer& renderer, Camera3D& camera, uint32_t imageIndex) = 0;
			virtual void destroy(Renderer& renderer) = 0;
			virtual VkPipelineLayout getPipelineLayout() const = 0;
		};
	}
}