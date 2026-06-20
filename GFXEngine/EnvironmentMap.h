#pragma once
#include "Entity.h"
#include "Asset.h"
#include "PositionMesh.h"
#include "EnvironmentMaterial.h"
#include <memory>
#include <cassert>
#include <filesystem>

namespace GFXEngine {
	namespace Graphics {

		class EnvironmentMap : public Asset, public GraphicsAsset, public FileAsset
		{
		private:
			std::unique_ptr<PositionMesh> m_mesh;
			std::unique_ptr<EnvironmentMaterial> m_envMaterial;
			std::vector<LibGFX::Buffer> m_uniformBuffers;
			std::vector<VkDescriptorSet> m_descriptorSets;
			bool m_initialized = false;
			bool m_loaded = false;

			//************************************
			// Method:    updateUniformBuffer
			// FullName:  GFXEngine::Graphics::EnvironmentMap::updateUniformBuffer
			// Access:    private 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			void updateUniformBuffer(Renderer& renderer, uint32_t imageIndex);

		public:
			float horizonFactor = 1.0f;
			float horizonFogExponent = 1.5f;
			float fogDensity = 0.00f;

			//************************************
			// Method:    EnvironmentMap
			// FullName:  GFXEngine::Graphics::EnvironmentMap::EnvironmentMap
			// Access:    public 
			// Returns:   
			// Qualifier: : Asset(name), FileAsset(filePath)
			// Parameter: const std::string & name
			// Parameter: const std::string & filePath
			//************************************
			EnvironmentMap(const std::string& name, const std::string& filePath) : Asset(name), FileAsset(filePath) {}

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::EnvironmentMap::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			void init(GFXEngine::Graphics::Renderer& renderer) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::EnvironmentMap::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			void destroy(GFXEngine::Graphics::Renderer& renderer) override;
			
			//************************************
			// Method:    isInitialized
			// FullName:  GFXEngine::Graphics::EnvironmentMap::isInitialized
			// Access:    public 
			// Returns:   bool
			// Qualifier: const 
			//************************************
			bool isInitialized() const override;

			//************************************
			// Method:    load
			// FullName:  GFXEngine::Graphics::EnvironmentMap::load
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void load() override;
			
			//************************************
			// Method:    unload
			// FullName:  GFXEngine::Graphics::EnvironmentMap::unload
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void unload() override;
			
			//************************************
			// Method:    isLoaded
			// FullName:  GFXEngine::Graphics::EnvironmentMap::isLoaded
			// Access:    public 
			// Returns:   bool
			// Qualifier: const 
			//************************************
			bool isLoaded() const override;

			//************************************
			// Method:    update
			// FullName:  GFXEngine::Graphics::EnvironmentMap::update
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			void update(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			
			//************************************
			// Method:    getMaterial
			// FullName:  GFXEngine::Graphics::EnvironmentMap::getMaterial
			// Access:    public 
			// Returns:   const GFXEngine::Graphics::EnvironmentMaterial&
			// Qualifier: const
			//************************************
			const EnvironmentMaterial& getMaterial() const { 
				assert(m_envMaterial);
				return *m_envMaterial; 
			}

			//************************************
			// Method:    getMesh
			// FullName:  GFXEngine::Graphics::EnvironmentMap::getMesh
			// Access:    public 
			// Returns:   const GFXEngine::Graphics::PositionMesh&
			// Qualifier: const
			//************************************
			const PositionMesh& getMesh() const { 
				assert(m_mesh);
				return *m_mesh; 
			}

			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::EnvironmentMap::getDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier: const
			// Parameter: uint32_t imageIndex
			//************************************
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const {
				assert(imageIndex < m_descriptorSets.size());
				return m_descriptorSets[imageIndex];
			}
		};
	}
}