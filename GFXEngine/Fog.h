#pragma once
#include "Renderer.h"
#include "glm/glm.hpp"
#include "ISerializable.h"
#include "Camera.h"

namespace GFXEngine {
	namespace Graphics {
		class Fog : public ISerializable
		{
		private:
			std::vector<LibGFX::Buffer> m_uniformBuffers;
			std::vector<VkDescriptorSet> m_descriptorSets;

		public:
			float density = 0.3f;
			float minDistance = 25.0f;
			float maxDistance = 5000.0f;
			glm::vec4 color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);


			void init(Renderer& renderer);
			void update(Renderer& renderer, const Camera& camera, uint32_t imageIndex);
			void destroy(Renderer& renderer);

			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const { return m_descriptorSets[imageIndex]; }

			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, SerializationContext& context, SerializationFlags flags = SerializationFlags::None) override;

		};
	}
}
