#pragma once
#include "Material.h"
#include "Imaging.h"
#include <string>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Material class specifically designed for rendering sprites. 
		/// It manages a texture and its associated descriptor set, 
		/// and uses a graphics pipeline for rendering.
		/// </summary>
		class SpriteMaterial : public Material {

		public:
			SpriteMaterial(const std::string& texturePath) 
				: m_texturePath(texturePath) {}

			void init(Renderer& renderer) override;
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_textureDescriptorSet; }
			void destroy(Renderer& renderer) override;

		private:
			std::string m_texturePath;
			LibGFX::Image m_texture;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;
		};
	}
}