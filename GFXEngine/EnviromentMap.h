#pragma once
#include "Entity.h"
#include "Asset.h"
#include "PositionMesh.h"
#include "EnviromentMaterial.h"
#include <memory>
#include <cassert>
#include <filesystem>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// EnviromentMap asset type
		/// </summary>
		class EnviromentMap : public GFXEngine::Asset
		{
		private:
			std::unique_ptr<PositionMesh> m_mesh;
			std::unique_ptr<EnviromentMaterial> m_envMaterial;
			std::vector<LibGFX::Buffer> m_uniformBuffers;
			std::vector<VkDescriptorSet> m_descriptorSets;

			void updateUniformBuffer(Renderer& renderer, uint32_t imageIndex);

		public:
			float horizonFactor = 1.0f;
			float horizonFogExponent = 1.5f;
			float fogDensity = 0.00f;

			EnviromentMap(const std::string& name, const std::filesystem::path& filePath);
			EnviromentMap(const std::string& name, const std::vector<std::string>& faceFilepaths);

			void init(GFXEngine::Graphics::Renderer& renderer);
			void update(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			void destroy(GFXEngine::Graphics::Renderer& renderer);

			void setHorizonFactor(float factor) { horizonFactor = factor; }
			void setHorizonFogExponent(float exponent) { horizonFogExponent = exponent; }

			const EnviromentMaterial& getMaterial() const { 
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