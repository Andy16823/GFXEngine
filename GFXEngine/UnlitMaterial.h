#pragma once
#include "Material.h"
#include "Imaging.h"


namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// UnlitMaterial is a material that does not respond to lighting and is rendered with a texture. 
		/// It is used for objects that do not require lighting calculations, such as UI elements or 2D sprites.
		/// </summary>
		class UnlitMaterial 
			: public Material {

		private:
			LibGFX::Image m_texture;
			std::string m_texturePath;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;

		public:

			UnlitMaterial(const std::string& texturePath) 
				: m_texturePath(texturePath) {}

			void init(Renderer& renderer) override;
			void updateMaterial(Renderer& renderer) override;
			void destroy(Renderer& renderer) override;
			
		public:
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_textureDescriptorSet; }
			
			
		};
	}
}
