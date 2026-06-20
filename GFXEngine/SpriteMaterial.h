#pragma once
#include "Material.h"
#include "Imaging.h"
#include <string>

namespace GFXEngine {
	namespace Graphics {

		class SpriteMaterial : public Material {
		private:
			std::string m_texturePath;
			LibGFX::Image m_texture;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;

		public:
			//************************************
			// Method:    SpriteMaterial
			// FullName:  GFXEngine::Graphics::SpriteMaterial::SpriteMaterial
			// Access:    public 
			// Returns:   
			// Qualifier: : m_texturePath(texturePath)
			// Parameter: const std::string & texturePath
			//************************************
			SpriteMaterial(const std::string& texturePath) 
				: m_texturePath(texturePath) {}

		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::SpriteMaterial::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer) override;
			
			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::SpriteMaterial::getDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier: const 
			// Parameter: uint32_t imageIndex
			//************************************
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_textureDescriptorSet; }
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::SpriteMaterial::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer) override;
		};
	}
}