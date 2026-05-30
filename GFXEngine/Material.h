#pragma once
#include <vulkan/vulkan.h>
#include "Renderer.h"
#include "IRenderContributor.h"

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
			virtual void destroy(Renderer& renderer) = 0;
			virtual VkDescriptorSet getDescriptorSet() const = 0;

		};
	}
}