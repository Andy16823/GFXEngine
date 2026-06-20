#pragma once
#include "Material.h"
#include "Imaging.h"
#include "Renderer.h"

namespace GFXEngine {
	namespace Graphics {
		class PBRMaterial : public Material
		{
		private:
			LibGFX::ImageData m_albedoData;
			LibGFX::ImageData m_normalData;
			LibGFX::ImageData m_metallicRoughnessData;
			LibGFX::ImageData m_aoData;

			LibGFX::Image m_albedo;
			LibGFX::Image m_normal;
			LibGFX::Image m_metallicRoughness;
			LibGFX::Image m_ao;

			VkDescriptorSet m_descriptorSet = VK_NULL_HANDLE;

		public:
			
			//************************************
			// Method:    PBRMaterial
			// FullName:  GFXEngine::Graphics::PBRMaterial::PBRMaterial
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			PBRMaterial() = default;

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::PBRMaterial::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer) override;
			
			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::PBRMaterial::getDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier: const 
			// Parameter: uint32_t imageIndex
			//************************************
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_descriptorSet; }
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::PBRMaterial::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer) override;

			//************************************
			// Method:    setAlbedoTexture
			// FullName:  GFXEngine::Graphics::PBRMaterial::setAlbedoTexture
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::ImageData albedoData
			//************************************
			void setAlbedoTexture(LibGFX::ImageData albedoData) { m_albedoData = std::move(albedoData); }
			
			//************************************
			// Method:    setNormalTexture
			// FullName:  GFXEngine::Graphics::PBRMaterial::setNormalTexture
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::ImageData normalData
			//************************************
			void setNormalTexture(LibGFX::ImageData normalData) { m_normalData = std::move(normalData); }
			
			//************************************
			// Method:    setMetallicRoughnessTexture
			// FullName:  GFXEngine::Graphics::PBRMaterial::setMetallicRoughnessTexture
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::ImageData metallicRoughnessData
			//************************************
			void setMetallicRoughnessTexture(LibGFX::ImageData metallicRoughnessData) { m_metallicRoughnessData = std::move(metallicRoughnessData); }
			
			//************************************
			// Method:    setAOTexture
			// FullName:  GFXEngine::Graphics::PBRMaterial::setAOTexture
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::ImageData aoData
			//************************************
			void setAOTexture(LibGFX::ImageData aoData) { m_aoData = std::move(aoData); }
		};
	}
}