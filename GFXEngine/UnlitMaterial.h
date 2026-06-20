#pragma once
#include "Material.h"
#include "Imaging.h"


namespace GFXEngine {
	namespace Graphics {

		class UnlitMaterial : public Material {
		private:
			LibGFX::Image m_texture;
			std::string m_texturePath;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;

		public:
			//************************************
			// Method:    UnlitMaterial
			// FullName:  GFXEngine::Graphics::UnlitMaterial::UnlitMaterial
			// Access:    public 
			// Returns:   
			// Qualifier: : m_texturePath(texturePath)
			// Parameter: const std::string & texturePath
			//************************************
			UnlitMaterial(const std::string& texturePath) 
				: m_texturePath(texturePath) {}

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::UnlitMaterial::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer) override;
			
			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::UnlitMaterial::getDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier: const 
			// Parameter: uint32_t imageIndex
			//************************************
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_textureDescriptorSet; }
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::UnlitMaterial::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer) override;
		};
	}
}
