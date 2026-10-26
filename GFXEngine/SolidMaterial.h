#pragma once
#include "Material.h"
#include "Renderer.h"
#include <vector>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// SolidMaterial is a material that uses a single color for rendering. 
		/// It is used for objects that do not require textures.
		/// </summary>
		class SolidMaterial 
			: public Material
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
			void setColor(const glm::vec4& value) { m_color = value; }
			glm::vec4 getColor() const { return m_color; }
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_decriptorSet; }

		public:
			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;
		};
	}
}
