#pragma once
#include "Material.h"
#include "OptionalRef.h"
#include "Imaging.h"

namespace GFXEngine {
	namespace Graphics {
		class EnvironmentMaterial : public Material
		{
		private:
			LibGFX::CubemapData m_cubemapData;
			LibGFX::Cubemap m_cubemap;
			VkDescriptorSet m_cubemapDescriptorSet;

		public:
			
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::EnvironmentMaterial::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::EnvironmentMaterial::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer) override;
			
			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::EnvironmentMaterial::getDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier: const 
			// Parameter: uint32_t imageIndex
			//************************************
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_cubemapDescriptorSet; }

			//************************************
			// Method:    setCubemapData
			// FullName:  GFXEngine::Graphics::EnvironmentMaterial::setCubemapData
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::CubemapData data
			//************************************
			void setCubemapData(LibGFX::CubemapData data) { m_cubemapData = std::move(data); }
		};
	}
}
