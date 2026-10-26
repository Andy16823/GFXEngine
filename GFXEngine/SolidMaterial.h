#pragma once
#include "Material.h"
#include "Renderer.h"
#include <vector>

namespace GFXEngine {
	namespace Graphics {
		class SolidMaterial : public Material
		{
		private:
			VkDescriptorSet m_decriptorSet = VK_NULL_HANDLE;
			glm::vec4 m_color = glm::vec4(1.0);
			LibGFX::Buffer m_buffer;

		public:
			SolidMaterial() = default;

		public:
			void init(Renderer& renderer) override;
			void updateMaterial(Renderer& renderer) override;
			void destroy(Renderer& renderer) override;

		public:
			void setColor(const glm::vec4& value) { m_color = value; } // TODO: Make color updatable
			glm::vec4 getColor() const { return m_color; }
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_decriptorSet; }

		public:
			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;

		};
	}
}
