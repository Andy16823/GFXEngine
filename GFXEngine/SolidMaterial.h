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
			//************************************
			// Method:    SolidMaterial
			// FullName:  GFXEngine::Graphics::SolidMaterial::SolidMaterial
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			SolidMaterial() = default;

		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::SolidMaterial::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::SolidMaterial::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer) override;
			
			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::SolidMaterial::getDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier: const 
			// Parameter: uint32_t imageIndex
			//************************************
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_decriptorSet; }
			
			//************************************
			// Method:    setColor
			// FullName:  GFXEngine::Graphics::SolidMaterial::setColor
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec4 & value
			//************************************
			void setColor(const glm::vec4& value) { m_color = value; } // TODO: Make color updatable
			
			//************************************
			// Method:    getColor
			// FullName:  GFXEngine::Graphics::SolidMaterial::getColor
			// Access:    public 
			// Returns:   glm::vec4
			// Qualifier: const
			//************************************
			glm::vec4 getColor() const { return m_color; }
		};
	}
}
