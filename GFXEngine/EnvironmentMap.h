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
		/// EnvironmentMap class represents an environment map asset that can be used for rendering skyboxes 
		/// or reflections in a 3D scene. It manages the loading, initialization, and destruction of 
		/// the associated mesh and material resources, as well as uniform buffers and descriptor sets for rendering.
		/// </summary>
		class EnvironmentMap 
			: public Asset, public GraphicsAsset, public FileAsset
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
			float horizonFactor = 1.0f;
			float horizonFogExponent = 1.5f;
			float fogDensity = 0.00f;

			EnvironmentMap(const std::string& name, const std::string& filePath) 
				: Asset(name) { this->setFilePath(filePath); }

			void init(GFXEngine::Graphics::Renderer& renderer) override;
			void destroy(GFXEngine::Graphics::Renderer& renderer) override;
			bool isInitialized() const override;
			void load() override;
			void unload() override;
			bool isLoaded() const override;
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