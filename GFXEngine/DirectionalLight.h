#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "DataTypes.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// DirectionalLight represents a light source that emits parallel rays of light in a specific direction, simulating sunlight or other distant light sources. 
		/// It is defined by its direction and color, and it affects the entire scene uniformly regardless of the position of objects.
		/// </summary>
		class DirectionalLight
		{
		public:
			DirectionalLight() = default;
			~DirectionalLight() = default;

			DirectionalLight(const DirectionalLight&) = delete;
			DirectionalLight& operator=(const DirectionalLight&) = delete;
			
			DirectionalLight(DirectionalLight&&) = default;
			DirectionalLight& operator=(DirectionalLight&&) = default;

			void init(Renderer& renderer);
			void update(Renderer& renderer, const Camera& camera, uint32_t imageIndex);
			void bind(Renderer& renderer, const Camera& camera, const LibGFX::Pipeline& pipeline, uint32_t firstSet, uint32_t imageIndex) const;
			void destroy(Renderer& renderer);

			glm::vec3 direction = glm::vec3(-0.5f, -1.0f, -0.3f);
			glm::vec3 color = glm::vec3(1.0f, 0.95f, 0.9f);
			float intensity = 3;
		private:
			std::vector<LibGFX::Buffer> m_uniformBuffers;
			std::vector<VkDescriptorSet> m_descriptorSets;
		};
	}
}
