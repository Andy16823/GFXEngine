#pragma once
#include "Material.h"
#include "Imaging.h"
#include <string>

namespace GFXEngine {
	namespace Graphics {
		class PBRMaterial : public Material
		{
		public:
			PBRMaterial() = default;

			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, const Camera& camera, const LibGFX::Pipeline& pipeline, uint32_t imageIndex) const override;
			void destroy(Renderer& renderer) override;

			void setAlbedoTexture(LibGFX::ImageData albedoData) { m_albedoData = std::move(albedoData); }
			void setNormalTexture(LibGFX::ImageData normalData) { m_normalData = std::move(normalData); }
			void setMetallicRoughnessTexture(LibGFX::ImageData metallicRoughnessData) { m_metallicRoughnessData = std::move(metallicRoughnessData); }
			void setAOTexture(LibGFX::ImageData aoData) { m_aoData = std::move(aoData); }

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
		};
	}
}