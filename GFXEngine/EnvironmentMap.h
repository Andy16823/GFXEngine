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

		/// <summary>
		/// EnvironmentMap asset type
		/// </summary>
		class EnvironmentMap : public Asset, public GraphicsAsset, public FileAsset
		{
		private:
			std::unique_ptr<PositionMesh> m_mesh;
			std::unique_ptr<EnvironmentMaterial> m_envMaterial;
			std::vector<LibGFX::Buffer> m_uniformBuffers;
			std::vector<VkDescriptorSet> m_descriptorSets;
			bool m_initialized = false;
			bool m_loaded = false;

			void updateUniformBuffer(Renderer& renderer, uint32_t imageIndex);

		public:
			// Configurable parameters for the environment map
			float horizonFactor = 1.0f;
			float horizonFogExponent = 1.5f;
			float fogDensity = 0.00f;

			// Constructors
			EnvironmentMap(const std::string& name, const std::string& filePath) : Asset(name), FileAsset(filePath) {}

			// GraphicsAsset interface implementation
			void init(GFXEngine::Graphics::Renderer& renderer) override;
			void destroy(GFXEngine::Graphics::Renderer& renderer) override;
			bool isInitialized() const override;

			// FileAsset interface implementation
			void load() override;
			bool isLoaded() const override;

			// Own member functions
			void update(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			
			const EnvironmentMaterial& getMaterial() const { 
				assert(m_envMaterial);
				return *m_envMaterial; 
			}

			const PositionMesh& getMesh() const { 
				assert(m_mesh);
				return *m_mesh; 
			}

			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const {
				assert(imageIndex < m_descriptorSets.size());
				return m_descriptorSets[imageIndex];
			}
		};
	}
}